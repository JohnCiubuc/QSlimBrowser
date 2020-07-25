

## QSlimBrowser

This is a simple Qt [QWebEngineView](https://doc.qt.io/qt-5/qtwebengine-overview.html)  container that loads a URL from an [argument](https://www.bleepingcomputer.com/tutorials/understanding-command-line-arguments-and-how-to-use-them/) or, if no arguments are given, will just open Google. 

## Building

```bash
git clone https://github.com/JohnCiubuc/QSlimBrowser.git
cd QSlimBrowser
mkdir build && cd build
cmake .. && make
```

## Usage
```bash
QSlimBrowser [URL]
```
Where url is in quotation marks or back escaped (if your shell allows it), examples:
```bash
QSlimBrowser "http://google.com"
```
```bash
QSlimBrowser http:\/\/google.com
```
## Advance Usage
QSlimBrowser has the ability to **automate actions** and to **inject CSS** into a webpage. This is very useful if you want to auto-login into a webapp and have a userstyle applied to it.

There is a **Scripts** folder and a **Userstyles** folder. These folders ***must be in the same directory as the executable***. Following the **Building** instructions above should copy the folders into the *build* directory for you automatically. I'll figure out a smarter way to do this in the future

----

The **Scripts** folder contains a few automated logins showing text entry and button clicking for various websites. If so desired, the `TextField` portion of a script can be ignored. This allows for automated button clicking on a specified webpage

The **Userstyles** folder contains various user.css stylesheets taken from my [Userstyles](https://github.com/JohnCiubuc/userstyles) repo. Standard syntax for Userstyles should work, and they will inject on the webpage (singular) as specified on the stylesheet. Userstyles will inject as long as the domain contains the matched domain on the userstyle.

## Scriptable Commands

General Syntax:
```batch
Command
	Arguments
```
Each script needs to have a `Domain` specified with the `url` in the arguments. Domains are **absolute** i.e. the script will only execute if the current page url is *exactly* the one under `Domain`

### Command List
```batch
Domain
	URL

TextFieldByID
	ID
	Text_To_Enter

TextFieldBySelector
	Selector
	Text_To_Enter

ButtonByID
	ID_Of_Button_To_Click

ButtonBySelector
	Selector_Of_Button_To_Click
```

#### Script Example
```batch
Domain
    https://www.amboss.com/us/account/login
TextFieldByID
    signin_username
    john.doe@gmail.com
TextFieldByID
    signin_password
    password123
ButtonBySelector
    input[type="submit"]
```
Explanation:

On the domain `https://www.amboss.com/us/account/login`, find the text field by the id of `signin_username` and type `john.doe@gmail.com`. Then find the text field by the id of `signin_password` and type `password123`. Finally, search for the first element that matches `input[type="submit"]` and Click it

More examples can be found in the **Scripts** folder

	
## Screenshots
![github](https://github.com/JohnCiubuc/QSlimBrowser/raw/master/Images/github.png)
![google](https://github.com/JohnCiubuc/QSlimBrowser/raw/master/Images/google.png)
