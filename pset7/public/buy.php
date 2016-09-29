<?php
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {

        // render buy form
        render("buy_form.php", ["title" => "Buy"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //dump($_POST);
        if ($_POST["symbol"] == '')
        {
            apologize("You didn't enter a symbol. Please enter one and try again.");
        }
        
        else if ($_POST["shares"] == '')
        {
            apologize("You didn't enter a number. Please enter one and try again.");
        }

        // use lookup function to check price of stock
        $stock = lookup($_POST["symbol"]);
    
        // validate symbol entry
        if ($stock == false)
        {
            apologize("The symbol you entered doesn't seem to be valid. Please enter another.");
        }
        
        // ensure quantity of shares entered is a non-negative integer
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("You need to enter a whole number. Please try again.");
        }
        
        // calculate total cost of purchase and see if the user can afford it
        $noOfShares = $_POST["shares"];
        $totalCost = $noOfShares * $stock["price"];
        $cashArray = cs50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $userCash = $cashArray[0]["cash"] - $totalCost;
        
        // format numbers to ensure 2 decimal places after the 0
        $userCashFormatted = number_format($userCash, 2, '.', '');
        $totalCostFormatted = number_format($totalCost, 2, '.', '');
;
        
        if ($totalCost > $userCash)
        {
            apologize("You have insufficient funds for this transaction. Please check your balance and try again. You can deposit more cash by clicking the 'Deposit Cash' link in the navigation bar.");
        }
        
        else
        {   
            // remove stock from portfolios table and update cash in users table
            cs50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $_POST["shares"]);
            cs50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $totalCost, $_SESSION["id"]);
            
            // add transaction to history table
            $transactionType = "Purchase";
            cs50::query("INSERT INTO history (user_id, type, symbol, name, shares, price) VALUES(?, ?, ?, ?, ?, ?)", $_SESSION["id"], $transactionType, $stock["symbol"], $stock["name"], $_POST["shares"], $stock["price"]);
        }
        
        // render buy
        render("buy.php", ["title" => "Buy", "stock" => $stock, "post" => $_POST, "totalCostFormatted" => $totalCostFormatted, "userCashFormatted" => $userCashFormatted]);
    }
?>
