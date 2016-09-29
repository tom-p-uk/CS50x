<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Enter stock symbol" type="text"/>
        </div>
        <div class="form-group">
            <label for="deposit">
                Shares
            </label>
            <input type="number" name="shares" min="1" max="10000" placeholder="0">
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Buy
            </button>
        </div>
    </fieldset>
</form>