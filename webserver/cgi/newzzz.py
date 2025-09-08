#!/usr/bin/env python3

import os
import sys
from urllib.parse import parse_qs

# --- Step 1: Read and Parse the Request ---

# The web server passes data to a CGI script in two main ways:
# - For GET requests, data is in the 'QUERY_STRING' environment variable.
# - For POST requests, data is in the request body, which we read from standard input.

# We'll store the parsed form data in this dictionary.
form_data = {}

# Check the request method
request_method = os.environ.get('REQUEST_METHOD', 'GET')

if request_method == 'POST':
    # Get the length of the content from the environment variable
    try:
        content_length = int(os.environ.get('CONTENT_LENGTH', 0))
    except (ValueError):
        content_length = 0

    # Read that many bytes from standard input (the request body)
    post_body = sys.stdin.read(content_length)
    
    # Parse the URL-encoded string (e.g., "name=John&age=30") into a dictionary
    form_data = parse_qs(post_body)

elif request_method == 'GET':
    # For GET, the data is in the query string
    query_string = os.environ.get('QUERY_STRING', '')
    form_data = parse_qs(query_string)

# The `parse_qs` function returns a dictionary where values are lists.
# We'll extract the first value from each list, or default to an empty string.
# Example: {'name': ['Alice'], 'age': ['30']} -> name = 'Alice', age = '30'
name = form_data.get('name', [''])[0]
age = form_data.get('age', [''])[0]


# --- Step 2: Print the HTTP Header and HTML Content ---

# This header is essential for the browser to understand the content.
print("Content-Type: text/html")
print()  # A blank line must separate the header from the body.

# HTML boilerplate
print("<html>")
print("<head><title>Modern CGI Script</title></head>")
print("<body>")
print("<h1>Modern CGI Script (No 'cgi' module)</h1>")

# Print HTML form. The action points to the script itself.
# It's good practice to use os.environ['SCRIPT_NAME'] to make it portable.
script_name = os.environ.get('SCRIPT_NAME', '')
print(f"<form method='post' action='{script_name}'>")
print("Name: <input type='text' name='name'><br>")
print("Age: <input type='text' name='age'><br>")
print("<input type='submit' value='Submit'>")
print("</form>")

# Print submitted data if it exists
if name or age:
    print("<h2>Submitted Data:</h2>")
    # Basic escaping to prevent HTML injection from user input
    name_escaped = name.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
    age_escaped = age.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
    print(f"<p>Name: {name_escaped}</p>")
    print(f"<p>Age: {age_escaped}</p>")

print("</body></html>")
