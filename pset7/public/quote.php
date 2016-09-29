<?php
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // use lookup function to check price of stock
        $stock = lookup($_POST["symbol"]);
    
        // validate entry
        if ($stock != false)
        {
            extract($stock);
            render("quote.php", ["title" => "Quote", "symbol" => $symbol, "name" => $name, "price" => $price]);
        }
        
        else
        {
            apologize("The symbol you entered doesn't seem to be valid. Please enter another.");
        }

    }

?>