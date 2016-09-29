<div class="container">
    <h4>Current Stock Portfolio:</h4>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Company Name</th>
                <th>Symbol</th>
                <th>Share Price</th>
                <th>Number of Shares</th>
            </tr>
        </thead>
        <?php foreach ($positions as $position): ?>
        <tbody>
            <tr>
                <td><?= $position["name"] ?></td>
                <td><?= $position["symbol"] ?></td>
                <td>$<?= $position["price"] ?></td>
                <td><?= $position["shares"] ?></td>
            </tr>
        </tbody>
        <?php endforeach ?>
    </table>
</div>
<div class="cash_amount">
    <p><br>You have a total of <b>$<?= $cashFormatted ?></b> remaining.</p>
</div>