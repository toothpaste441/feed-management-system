# social media feed management system

The Social Media Feed Management System is a C++ application designed to simulate the functionality of a social media platform. 
It allows users to manage posts, update interactions, and view posts based on popularity and recency. This application offers an intuitive 
interface and efficient feed management.

Features:

1. Add New Posts:
Create posts with unique IDs and content to populate the feed. The IDs are automatically taken in the order of adding. 
For ex: the 1st post has ID = 001 and nth post has ID=n;

2. Like a  Posts:
Update the interaction score (e.g., likes) of a post, enhancing its relevance in the feed.

3. Get Trending Posts:
Retrieve the top 10 most engaging posts ranked by interaction scores and recency.

4. Remove Oldest Post:
Maintain an updated feed by removing the oldest post, ensuring focus on newer content.

5. Display Latest Posts:
Review all posts in reverse chronological order, starting with the most recent.

6. Share post:
The user can choose which post to share with the ID.

7. Find post by ID
Tells the number of likes on the selected post and the timestamp of when it was added

8. Get most shared and get most liked
This works as a filter and user can choose any of the two options and they will get the order in descending order.

9. Exit:
Safely close the application at any time.

How It Works:-

The following data structures have been used:

-Unordered Maps for quick access and updates.
-Linked Lists to maintain chronological order.
-Priority Queues to rank posts by engagement and time for trending posts.
The design ensures efficiency and relevance for all feed-related actions.

Instructions for Use:-

1. Launch the Program

2. Compile the code using a C++ compiler.

3. Run the program to access the menu-driven interface.

4. Select any of the 8 Menu Options. Use the numeric menu to add, interact with, or manage posts and Perform Actions. 

5. Follow on-screen prompts for each selected option.

6. Exit. Use the exit option to safely terminate the program.

Future Enhancements:-
User Profiles: Introduce multi-user functionality.
Advanced Metrics: Add support for comments and shares.
Data Persistence: Implement database or file-based storage for posts.
Customizable Feeds: Enable sorting by user-defined criteria

Contributors:-
M. CHINMAI BM23BTECH11016
ISHWARYA A BM23BTECH11009

Project context:
This project was developed to demonstrate the effective use of data structures and algorithms in real-world applications.

Disclaimer:-
This application is a project developed for educational purposes and is not intended for deployment as a fully functional social media 
platform. Use of this application in production environments is at the user’s own discretion. The developers are not liable for any 
issues arising from misuse. 

Acknowledgments:-
Special thanks to the contributors and educators who provided guidance during its development.
-----------------------------------------------------------end--------------------------------------------------------------------------
