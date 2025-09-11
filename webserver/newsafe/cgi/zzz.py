#!/usr/bin/env python3

import cgi

# Print necessary headers
# HTML boilerplate
print("<html><head><title>Simple CGI Script with cgi module</title></head>")
print("<body>")
print("<h1>Simple CGI Script with cgi module</h1>")

# Create instance of FieldStorage
form = cgi.FieldStorage()

x = 5
name = ""
age = ""
name1 = ""
age1 = ""
name2 = ""
age2 = ""
name3 = ""
age4 = ""
name4 = ""
age3 = ""
name5 = ""
age5 = ""

# Get data from fields
try :
    name = form.getvalue('name')
    age = form.getvalue('age')
    name1 = "name1"
    age1 = "test"
    name2 = "random"
    age2 = "kanready"
    name3 = "1 b 1"
    age4 = x
    name4 = "hello {x}"
    age3 = key
    name5 = " aa"
    age5 = "bb"
except :
    print("No name nor age")


# Print HTML form
print("<form method='post' action='python.py'>")
print("Name: <input type='text' name='name'><br>")
print("Age: <input type='text' name='age'><br>")
print("<input type='submit' value='Submit'>")
print("</form>")

# Print submitted data
if name or age:
    print("<h2>Submitted Data:</h2>")
    print("<p>Name: {}</p>".format(name))
    print("<p>Age: {}</p>".format(age))
    print("<p>Age: {}</p>".format(age4))
    print("<p>Age: {}</p>".format(name4))
    print("<p>Age: {}</p>".format(name3))
    print("<p>Age: {}</p>".format(age4))



print("</body></html>")
