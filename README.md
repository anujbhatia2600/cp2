# Calorie Tracker

## Problem statement: 
Recently, it has been proven that health is very important for a human being and diet plays a vital role in one’s health. It is advised by numerous health organisations that everyone should to keep a track of their calorie intake to improve their diet and avoid junk. We will use our application to help families improve their diet by inputting their meals every day.

## Assumption: 
* The calories of the food items lies in the range 0-1000.
* The files linked with the Project can only be accessed through the program and user is not allowed to access these files from the backend.
* The Daily Intake file can never be empty and it has a column header row which can never be removed.
* A new day starts manually and not automatically, the user will have to reset his/her intake in the morning, this option has been provided.

## Problem setting: 
We want every person to stay aware of their diet, so they can stay fit and healthy in the long term. Hence, we aim on making a Calorie Tracker, wherein everyone can aim to acheive the optimum calorie intake and keep record of their daily calorie intake to eat healthy. 

## Functionalities:
The Calorie Tracker is a simple to use application wherein a user is supposed to enter his/her basic information like Name, Age, Height, Weight, Gender. The application then calculates the users optimum calorie intake based on the Mifflin-St. Jeor Equation (which the American Dietetic Association finds most reliable). Then the existing files are loaded into the struct files using the loadDailyIntake and loadCalDatabase functions which call the Intake and Calorie database file (CalFile.txt) respectively. Then the user gets various options in form of a menu:
* **ADD**: If the user selects add then the user can add a food item to the list and it calls the addFoodToIntake function. In this function the size of the intake dynamic array is increased by 1 after which the food item is searched in the calorie database using the search function. If found, name as well as calories corresponding to the food items are added to the intake file. If not found, the application asks the user to manually input the unknown food items' calories. Then this unknown items is added it to the users' daily intake file as well as the database. 
* **DELETE**: It gives the user a menu of the intakes so far and using a new dynamic array deletes the intake that the user want using a while loop storing the values in the new dynamic array. 
* **LIST**: The printList function is called where the persons' intake for the day is printed.
* **PRINT INFO**: This is used to print the information of the user by calling the various variable of the struct x of the datatype person.
* **PRINT**: Calculates the total calories intake so far in the day by calling the _CALCULATOR_ function. Also, prints the number of calories left for the day for the user.
* **UPDATE**: The updatedailyintake function is called where the application prints a list of the existing food items in the users day's intake and asks the user to choose which items needs to be updated.
* **UPDATE PERSONAL INFORMATION**: The updatePersonInfo fucntion is called where the the user is given an option to update their information, consequently the file that stores the users' information is updated with the new information. It also recalculates the optimum calories for a day.
* **RESET**: Calls the resetIntake function where the entire struct as well as file is cleared and hence the user can begin the day with an fresh daily intake list.

## Features:
The Calorie Tracker gives a list of options to the user to keep track of his health record:
* **ADD**: You can add the food items you have consumed. The calorie tracker searches for the item in our database and adds it to your daily food intake list. If the food item is not found in our database you get the option to add it to our database as well as your own list along with the calories of the food item.
* **DELETE**: Added a food item by mistake? The Calorie Tracker gives you the option to delete the food item from your list.
* **LIST**: The Calorie Tracker gives you the option to view all the food items that you have had throughout the day.
* **PRINT**: The Calorie Tracker prints the number of calories consumed by you so far in the day and also tells you the number of calories you can intake to reach optimum calorie intake.
* **UPDATE**: The Calorie Tracker also allows you to update your daily intake list and change it with another food item.
* **CHANGE INFORMATION**: The Calorie Tracker allows the user to change their own informations like, name, weigth, height, age and gender.
* **RESET**: When it's a new day, the user can simply use the reset function to clear the entire daily intakes and mark it as a new daily and start acheiving the optimum calorie intake.
## Input/Output Specifications:
* The inputs required are specified whenever the input is demanded and if the input is invalid then the program demands for a valid input.
* The output is directly shown to the user as well as gets stored in the files automatically as the user proceeds in the program.
## Compilation and Execution Instructions:
To access the program, the user needs to use terminal and follow the given steps:
1. The user needs to make sure that all the files are in the same location.
2. The user needs to move to that repository in the terminal which contains all the files using the cd command.
3. The user should compile all the files using the following command:"make census".
4. The user needs to now execute the compiled file by using:"./census".
Now the user can access our program.
* Note: It may be possible that the user maybe denied the access and in this situation the user can use :"chmod a+x census".
# SPECIAL FEATURE:
### The special feature that the program provides is that when a user inputs a item which already exist in our database, we give him/her the option to buy that product from us. This saves the users time as he/she will buy items according to their intake, so they won't need to go the supermarket to buy the usual items in their diet.  
The different function that are present under this special feature are:
* ADD: If the item is present in our database (before the start of the program), then the user can add this item into his/her cart.
* DELETE: The user can also delete items from the cart.
* VIEW: The user can view all the items present in the cart.


