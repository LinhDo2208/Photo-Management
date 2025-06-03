_After running the program, a function menu will be displayed. Users can interact with the program by entering the corresponding number from 1 to 7. The program includes the following functions:_

_**1. Add a new photo to the list**_

_**2. Show the list of photos**_

_**3. Search for photos by name**_

_**4. Edit photo information**_

_**5. Delete a photo**_

_**6. Recycle bin**_

_**7. Sort the photo list**_

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

**IV. Edit Photo Information**

- Select "4", and all the name of photos (without data) in the list and their indexes will be displayed.
- Enter the index corresponding to the name of photo which you want to edit.
- The message "New name: ", "New date of creation: ", "New date of modification: ", "New date of access: " will appear respectively for you to edit

  _(The size and the path of photo is constant so you can not edit these elements)._

**V. Delete a Photo**

- Select "5" to view all the name of photos in "photos.txt" (without data) and their indexes.
- Enter the index corresponding to the name of photo which you want to delete.
- The selected photo’s data will be removed from “photos.txt” and transferred to “Rubbish.txt” (the recycle bin).

**VI. Recycle Bin**
Select "6", all of photos in "Rubbish.txt" will be displayed. Moreover, there are 2 options for you:

_**a) Restore**_

- Select "1", all the name of photos in "Rubbish.txt" (without data) and their indexes will be shown.
- Enter the index corresponding to the name of photo which you want to store.
- The selected photo’s data will be deleted from “Rubbish.txt” and added to “photos.txt”.

_**b) Permanently Delete**_

- Select "2",  The remaining processes are similar to "a)".
- But, The selected photo’s data will not be added to “photos.txt”.

**VII. Sort**
 
Choose "7", there are 5 selections for you:

_**a)Sort by name**_

Choose "1". There are 2 options: _A-Z_ or _Z-A_

+) Select "1": the list of photos will be sorted by name from A to Z.

+) Select "2": the list of photos will be sorted by name from Z to A.

_**b) Sort by date of creation (date of modification, date of access, size)**_

Choose "2 (3, 4, 5, respectively)". There ar 2 option: _Ascending_ or _Descending_

+) Select "1": the list of photos will be sorted by date of creation (date of modification, date of access, size) in ascending order.

+) Select "2": the list of photos will be sorted by date of creation (date of modification, date of access, size) in descending order.

**VII. Exit**

Choose "0" in each menu to _Exit_ or _Back_.
