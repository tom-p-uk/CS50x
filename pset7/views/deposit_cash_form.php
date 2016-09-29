<form action="deposit_cash.php" method="post">
    <fieldset>
        <div class="form-group">
            <p>You may deposit up to $500 at a time.</p>
            <label for="deposit">
                $
            </label>
            <input type="number" name="deposit" min="1" max="500" placeholder="0" autofocus>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Deposit.
            </button>
        </div>
    </fieldset>
</form>