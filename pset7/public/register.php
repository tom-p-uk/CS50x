<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check for valid input in username, password and confirmation fields
        if ($_POST["username"] == '')
        {
            apologize("Sorry, you entered a blank username. Please enter a valid username.");
        }
        
        else if ($_POST["password"] == '')
        {
            apologize("Sorry, you entered a blank password. Please enter a valid password.");
        }
        
        else if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Sorry, your passwords do not match. Please enter matching passwords.");
        }

        // use query function to add user to database, using data from POST super var
        $result = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        // confirm status of function call
        if ($result == 0)
        {
            apologize("We couldn't register you at this time. Change your username and try again.");
        }
        
        // save id as variable, remember the session using the var and then redirect
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        $_SESSION["id"] = $id;
        redirect("/");
    }

?>