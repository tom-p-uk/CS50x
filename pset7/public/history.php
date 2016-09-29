<?php

    // configuration
    require("../includes/config.php"); 

    // run query for any shares in portfolio table that belong to the user
    $rows = CS50::query("SELECT type, symbol, name, shares, price, time FROM history WHERE user_id = ?", $_SESSION["id"]);
    
    // render portfolio
    render("history.php", ["title" => "Portfolio", "rows" => $rows]);

?>
