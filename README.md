# BookScout

BookScout is an interface that provides insights into the vocabulary used in literature by analyzing text files from Project Gutenberg. By identifying the most frequently used words, a word cloud is created that visually represents these words, making it easier for readers to grasp the common themes and language of a book.
Once the program is initiated it will display a user interface created with SFML and imported graphics designed on Canva. The mini library in the middle of the screen has five novels ready to be analyzed: AliceInWonderland, Treasure Island, Frankenstein, The Great Gatsby, and Jane Eyre. Each of these novels can be clicked on and this will open a new screen where the user can select which algorithm they would like to use to find the top thirty words in the novel they selected.

Languages Used:
Python and C++

Libraries:
SFML
MatPlotLib 
WordCloud

Attributes:
Word Frequency Analysis: Automatically analyze the most frequently used words in a book.
Word Clouds: Visual representation of the word frequencies using word clouds.
Algorithm Options: Choose between different string-matching algorithms like Knuth-Morris-Pratt or Boyer-Moore for word analysis.

Instructions for running the program:

Ensure that you have the libraries listed above are downloaded and that you are working with an IDE or interpreter that can read both python and C++. In order for the program to run correctly your files must be saved in the format shown below. This is neccesary for the program to run as relative file paths have been written into the code which are dependent on the structure in which you save each of these files. Additionally, if you are testing this code on a mac please account for the direction in which the slashes (/) are written for the filepaths to accomodate the Mac OS. 

Overarching Project Folder:
     
     images (folder titled "images" that contains all of the .png files)   
     main.cpp  
     bm.h 
     kmp.h 
     AliceInWonderland.txt
     JaneEyre.txt
     TreasureIsland.txt
     GreatGatsby.txt
     Frankenstein.txt
     wordCloud.py
     font.ttf

Once the files are saved correctly, and the repository is cloned, you may run the program by compiling and calling main.cpp file.




     
     

