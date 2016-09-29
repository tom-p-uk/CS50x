<?php

    // configuration
    require("../includes/config.php"); 

    // run query for any shares in portfolio table that belong to the user
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    
    // loop through rows, calling lookup each iteration and adding all data to new associative arrray
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $stock["symbol"]
            ];
        }
    }
    
    
    // run query for user's cash amount and save in cash variable
    $cashArray = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    $cashFormatted = number_format($cashArray[0]["cash"], 2, '.', '');
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cashFormatted" => $cashFormatted]);

?>
