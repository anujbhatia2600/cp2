# Calorie Tracker

## Problem statement: 
Recently, it has been proven that health is very important for a human being and diet plays a vital role in one’s health. It is advised by numerous health organisations that everyone should to keep a track of their calorie intake to improve their diet and avoid junk. We will use our application to help families improve their diet by inputting their meals every day.

## Assumption: 
* The calories of the food items lies in the range 0-1000.
* The files linked with the Project can only be accessed through the program and user is not allowed to access these files from the backend.
* The Daily Intake file ca never be empty and it has a column header row which can never be removed.
* A new day starts manually and not automatically.

## Problem setting: 
We want every person to stay aware of their diet, so they can stay fit and healthy in the long term. Hence, we aim on making a Calorie Tracker, wherein everyone can aim to acheive the optimum calorie intake and keep record of their daily calorie intake to eat healthy. 

## Functionalities:
The Calorie Tracker is a simple to use application wherein a user is supposed to enter his/her basic information like Name, Age, Height, Weight, Gender. The application then calculates the users optimum calorie intake based on the Mifflin-St. Jeor Equation( which the American Dietetic Association finds most reliable). Then the existing files are loaded into the strcut files using the loadDailyIntake and loadCalDatabase function which call the the Intake file and the CalFile as well. Then the user gets various options in form of menu:
* ADD: if the user selects it then the user can add a food item to the list and it calls the addFoodToIntake function. In this function the size of the intake dynamic array is increased by 1 after which the food item is searched in the calfile(our database) using the search function. If found then it adds the name as well as calories corresponding to it in the intake struct and file. If not found then it ask the user to input its calories. Then it adds it to the dailt y intake struct and file as well as our database. 
* DELETE: It gives the user a menu of the intakes so far and using a new dynamic array deletes the intake that the user want using a while loop storing the values in the new dynamic array. 
* LIST: This call the printList function where the list of the daily intake items so far is printed.
* PRINT INFO: This is used to print the information of the user by callin the various variable of the struct x of the datatype person.
* PRINT: Calculates the total calories intake so far by calling the CALCULATOR function. Also, prints the number of calories more that the user can intake.
* UPDATE: this calls the updatedailyintake function where it gives a menu to the user and updates the existing food item with the food item that the users want by the usage of the search fucntion and updates it in the daily intake struct and file.
* UPDATE PERSONAL INFORMATION: this calls the updatePersonInfo where the the user is given an option to update a information, then it updates the member file as well as person struct. It also recalculates the optimum calories.
* RESET: Calls the resetIntake function where the entire struct as well as file is cleared and hence the user can again begin from the first item.

## Features:
The Calorie Tracker gives a list of options to the user to keep track of his health record:
* ADD: You can add the food items you have consumed. The calorie tracker searches for the item in our database and adds it to your daily food intake list. If the food item is not found in our database you get the option to add it to our database as well as your own list along with the calories of the food item.
* DELETE: Added a food item by mistake? The Calorie Tracker gives you the option to delete the food item from your list.
* LIST: The Calorie Tracker gives you the option that you can view all the food items that you have had through out the day.
* PRINT: The Calorie Tracker prints the number of calories consumed by you so far in the day and also tells you the number of calories you can intake to reach optimum calorie intake.
* UPDATE: The Calorie Tracker also allows you to update your daily intake list and change it with another food item.
* CHANGE INFORMATION: The Calorie Tracker allows the user to change their own informations like, name, weigth, height, age and gender.
* RESET: To change the day the user can simply use the reset function to clear the entire daily intakes and mark it as a new daily and start acheiving the optimum calorie intake.
## Input/Output Specifications:
* The inputs required are specified whenever the input is demanded and if the input is invalid then the program demands for a valid input.
* The output is directly shown to the user as well as gets stored in the files automatically as the user proceeds in the program.
## Compilation and Execution Instructions:
To access the program, the user needs to use the terminal and follow the given steps:
1. The user needs to make sure that all the files are in the same location.
2. The user needs to move to that repository in the terminal which contains all the files using the cd command.
3. The user should compile all the files using the following command:"make census".
4. The user needs to now execute the compiled file by using:"./census".
Now the user can access our program.
* Note: It may be possible that the user maybe denied the access and in this situation the user can use :"chmod a+x census".
### SPECIAL FEATURE:
# The special feature that the program provides is that when a user inputs a item which already exist in our database, we give him/her the option to buy that product from us. 
The different function that are present under this special feature are:
* ADD: If the item is present in our database(before the start of the program), then the user can add this item into his cart.
* DELETE: The user can also delete items from the cart.
* VIEW: The user can view all the items present in the cart.


