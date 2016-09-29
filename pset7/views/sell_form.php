<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <label for="dropdown">Select a stock</label>
            <select name="dropdown" id="dropdown" autofocus>
                <?php foreach ($positions as $position): ?>
                    <option name="nameSymbol" value=<?= $position["symbol"] ?>><?= $position["name"] ?> (<?= strtoupper($position["symbol"]) ?>)</option>
                <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit" name="submit" value="submit">
                Sell
            </button>
        </div>
    </fieldset>
</form>