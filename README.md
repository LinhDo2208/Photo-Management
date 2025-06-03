_After running the program, a function menu will be displayed. Users can interact with the program by entering the corresponding number from 1 to 7. The program includes the following functions:_

1. Add a new photo to the list

2. Show the list of photos

3. Search for photos by name

4. Edit photo information

5. Delete a photo

6. Recycle bin

7. Sort the photo list

**I. Add a New Photo to the List**
- Select “1” from the menu.
- The message “Enter the path:” will appear.
- Enter the full path to the photo file on your computer _(e.g: C:\Users\...\Pictures\image1.jpg)._
- The program will automatically collect information about the photo, including:
	+) File name
	+) Date of creation
	+) Date of modification
	+) Date of last access
	+) File size
- This information will be saved into the file “photos.txt”.
- After adding successfully, the list of photos will be displayed for the user to review.

**II. Display the List of Photos**
- Select “2” to view all saved photos.
- The program will read data from “photos.txt” and display information of each photo, including:
	+) File name
	+) Date of creation
	+) Date of modification
	+) Date of last access
	+) File size
	+) Path to the file on the computer

**III. Search for Photos by Name**
- Select “3” from the menu.
- The message “Enter the name of finding photo:” will appear.
- Enter full name or a part of the name of the photo.
	_For example: Enter “A” to find all photos whose names start with the letter A._
- The matching photos with all data of them will be displayed immediately.

IV. Edit photo information
- Select "4", and all the name of photos (without data) in the list in their index will be displayed.
- Enter the index corresponding to the name of photo which you want to edit.
- The message "New name: ", "New date of creation: ", "New date of modification: ", "New date of access: " will appear respectively for you to edit

  _(The size and the path of photo is constant so you can not edit these elements)._
