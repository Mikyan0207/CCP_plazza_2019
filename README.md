# CCP_plazza_2019

### Project's goal

The goal of this project is to run a fast food pizzeria.
This project, after being launched, is meant to receive orders threw a command prompt (the **reception**).  
The **reception** will dispatch pizzas between several **kitchens** so it requires a minimum of time to prepare an order.  
Each **kitchen** is a **process** and every **cook** is a **thread** of this process.  
Communication between the **reception** and the **kitchens** is made (locally) thanks to unix sockets.  

At the very beggining, no **kitchens** are open. A **kitchen** opens when an order has been received and no other **kitchens** are available (it can mean there are 0 **kitchens** open or that all the **kitchens** are busy with other orders).  
If a **kitchen** stays open for 5 seconds without having anything to do, it closes, leaving no zombie process or thread behind.

There are several sizes for pizzas : S = 1, M = 2, L = 4, XL = 8, XXL = 16.  

There are 4 types of pizzas :  
  - regina (baked in `1 * a * pizza_size` seconds) made with `doe, tomato, gruyere`
  - margarita (baked in `2 * a * pizza_size` seconds) made with `doe, tomato, gruyere, ham, mushrooms`
  - americana (baked in `2 * a * pizza_size` seconds) made with `doe, tomato, gruyere, steak`
  - fantasia (baked in `4 * a * pizza_size` seconds) made with `doe, tomato, eggplant, goat cheese, chief love`

Each **kitchen** has a maximum of 5 for each ingredient, which are shared between **cooks**.

### How to use it

Use the `make` instruction to compile the project.

Use the following commandline : `./plazza a b c`  
  - **a** being the cooking time multiplier for pizzas.  
  - **b** being the number of **cooks** per **kitchen** (must be an integer since it would not be very hygienic to have parts of a body inside the kitchens :smile:).  
  - **c** being the time in milliseconds needed by a kitchen to replace an ingredient.  

To place an order you MUST use the following syntax : `TYPE SIZE xNUMBER`.  
Orders can be separated by semicolons. Example : `regina XXL x2 ; fantasia M x3 ; margarita S x1`.  
You may want to use the `status` command to display the status of each kitchen in activity.
