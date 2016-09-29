<?php
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {

        // render deposit cash form
        render("deposit_cash_form.php", ["title" => "Desposit Cash"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate entry
        if ($_POST["deposit"] == '')
        {
            apologize("You didn't enter a number. Please enter one and try again.");
        }
        
        // query user's cash balance and add the money from the sale to it
        $existingBalance = cs50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $newBalance = $existingBalance[0]["cash"] + $_POST["deposit"];

        // update table with new cash figure
        cs50::query("UPDATE users SET cash = ? WHERE id = ?", $newBalance, $_SESSION["id"]);

        // render deposit cash
        render("deposit_cash.php", ["title" => "Deposit", "deposit" => $_POST["deposit"], "newBalance" => $newBalance]);
    }
?>
