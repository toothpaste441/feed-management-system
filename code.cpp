#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class Post {
public:
    int id;
    string content;
    int interaction_score; //likes
    int share_count;
    time_t timestamp;

Post(int id, const string &content) : id(id), content(content) { 
    interaction_score = 0;
    share_count = 0;
    timestamp = time(nullptr);
}

void update_interaction_score(int score) {
    interaction_score += score;
}

void share_post(){
    share_count++;
}

// prioritisation of posts for the option of trending posts 
//For equal scores, newest are priority and for unequal, the largest of them
bool operator<(const Post& other) const {      
    int score_a = interaction_score + share_count;
    int score_b = other.interaction_score + other.share_count;

    if (score_a == score_b) {
        return timestamp < other.timestamp;
    }
    return score_a > score_b;
    }
};

class Feed {
    unordered_map<int, list<Post>::iterator> post_map;  // Maps post ID to its iterator in the list
    list<Post> post_list;  // List of posts
    priority_queue<Post> post_heap;  // Max-heap for sorting posts
    int next_id = 1;

public:
    // user gets to add posts
    void add_post(const string &content) {
        int id = next_id++;
        Post new_post(id, content);
        post_list.push_front(new_post);
        post_map[id] = post_list.begin();
        post_heap.push(new_post);
    }

    void rebuild_heap() {
        priority_queue<Post> empty;
        swap(post_heap, empty);  

        for (const auto& post : post_list) {
            post_heap.push(post);
        }
    }

    // Update the interaction score of a post and reinsert it into the heap
    void interact_with_post(int id, int score) {
        if (post_map.find(id) != post_map.end()) {
            auto it = post_map[id];
            it->update_interaction_score(score);
            rebuild_heap();
        }
    }

    void share_post(int id) {
        if (post_map.find(id) != post_map.end()) {
            auto it = post_map[id];
            it->share_post();
            rebuild_heap();
            cout << "Post " << id << " shared successfully! Share count: " << it->share_count << endl;
        } else {
            cout << "Post with ID " << id << " not found." << endl;
        }
    }

    // Sorting and display is based on likes and shares combined 
void get_trending_posts() {
    if (post_list.empty()) {
        cout << "No posts available to display trending posts.\n";
        return;
    }

priority_queue<Post> temp_heap = post_heap;
cout << "Top 10 Trending Posts:\n";

    for (int i = 0; i < 10 && !temp_heap.empty(); ++i) {
        const Post& post = temp_heap.top();
        cout << post.id << ": Likes: " << post.interaction_score
             << ", Shares: " << post.share_count
             << "\nContent: " << post.content << "\n";
        temp_heap.pop();
    }
}
    
//usage of vector to store the posts and returns in descending order
void get_most_shared_posts() {
    if (post_list.empty()) {
    cout << "No posts available to display most shared posts.\n";
    return;
    }
vector<Post> shared_posts(post_list.begin(), post_list.end());

sort(shared_posts.begin(), shared_posts.end(), [](const Post& a, const Post& b) {
    return a.share_count > b.share_count;
    }
);

cout << "Top 10 Most Shared Posts:\n";
for (int i = 0; i < 10 && i < shared_posts.size(); ++i) {
    const Post& post = shared_posts[i];
    cout << post.id << ": Shares: " << post.share_count << "\nContent: " << post.content << "\n";
    }
}

// Generate the feed by returning the top n most relevant posts
vector<Post> get_most_liked_posts() {
    if (post_list.empty()) {
        cout << "No posts available to display most liked posts.\n";
        return {};  
    }
vector<Post> most_liked_posts(post_list.begin(), post_list.end());
sort(most_liked_posts.begin(), most_liked_posts.end(), [](const Post& a, const Post& b) {
        return a.interaction_score > b.interaction_score;
    }
);
    return most_liked_posts;
}

// Removes the oldest post from the feed by comparing timestamps
void remove_oldest_post() {
    if (post_list.empty()) {
        cout << "No posts to remove.\n";
        return;
    }

auto oldest_it = post_list.begin(); 
for (auto it = post_list.begin(); it != post_list.end(); ++it) {
    if (it->timestamp < oldest_it->timestamp) {
        oldest_it = it; 
    }
}
cout << "Removing Post ID: " << oldest_it->id << ", Timestamp: " << ctime(&(oldest_it->timestamp)) << endl;

post_map.erase(oldest_it->id);  
post_list.erase(oldest_it);    
rebuild_heap();  
}

// Display the feed in chronological order
void display_feed() {
    if (post_list.empty()) {
    cout << "No posts available in the feed.\n";
    return;
    }
cout << "Latest Posts:\n";
    
    for (auto it = post_list.rbegin(); it != post_list.rend(); ++it) {
        const Post& post = *it;
        string timestamp_str = ctime(&post.timestamp);
        timestamp_str.pop_back();
        cout << post.id << ": Likes: " << post.interaction_score << ", Timestamp: " << timestamp_str << "\nContent: " << post.content << "\n";
        }
    }

//displays the likes and timestamp of formation of that id
void find_post_by_id(int id) {
    if (post_map.find(id) != post_map.end()) {
        auto it = post_map[id];
        const Post& post = *it;
        cout << "Post Found:\n";
        cout << post.id << ": Likes: " << post.interaction_score << ", Timestamp: " << ctime(&post.timestamp) << "\nContent: " << post.content << "\n";
        } 
        else {
            cout << "Post with ID " << id << " is not found.\n";
        }
    }
};

// Main function
int main() {
    Feed myFeed;
    int choice;

cout << "\n=========================================================" << endl;
cout << "            WELCOME TO YOUR SOCIAL MEDIA PAGE!             " << endl;
cout << "=========================================================" << endl;

    cout << "\nPlease choose one of teh options below:\n";
    cout << "1. Add Post\n";
    cout << "2. Like a Post\n";
    cout << "3. Get Trending Posts\n";
    cout << "4. Remove Oldest Post\n";
    cout << "5. Latest Posts\n";
    cout << "6. Share a Post\n";
    cout << "7. Find post by ID\n";
    cout << "8. Get most shared\n";
    cout << "9. Get most liked\n";
    cout << "10. Exit\n";
    cout<<"----------------------------------------------------------\n"<<endl;

do {
cout << "Choose an option: ";
cin >> choice;
int id;
switch (choice) {
    case 1: {
        string content;
        cout << "Enter Post Content: ";
        cin.ignore();  
        getline(cin, content);
        myFeed.add_post(content);
        cout << "Post added successfully!\n";
            
        break;
    }
    case 2: {
        int score;
        cout << "Enter Post ID to interact with: ";
        cin >> id;
        cout << "Enter Likes: ";
        cin >> score;
        myFeed.interact_with_post(id, score);
        cout << "Likes updated!\n";
            
        break;
    }
    case 3: {
        myFeed.get_trending_posts(); 
        break;
    }
    case 4:
        myFeed.remove_oldest_post();
        cout << "Oldest post removed.\n";
                
        break;
    case 5:
        myFeed.display_feed();
            
        break;
    case 6:
        cout << "Enter Post ID to share: ";
        cin >> id;
        myFeed.share_post(id);
                
        break;
    case 7:
        cout << "enter post id to be searched" ;
        cin >> id;
        myFeed.find_post_by_id(id);
            
        break;
    case 8:
        myFeed.get_most_shared_posts();  
            
        break;
    case 9: {
        cout << "Top 10 Liked posts\n";
        vector<Post> top_posts = myFeed.get_most_liked_posts();
        for (const auto& post : top_posts) {
            cout << post.id << ": Likes: " << post.interaction_score << "\nContent: " << post.content << endl;
        }
        break;
    }
    case 10:
        cout << "Exiting feed\n";
                
        break;            
    default:
        cout << "Invalid option! Please try again.\n";
    }
    
} while (choice != 10);

    return 0;
}