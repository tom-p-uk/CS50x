<div class="container">
    <h4>Transaction Histoy:</h4>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Transaction Type</th>
                <th>Symbol</th>
                <th>Name</th>
                <th>Number of Shares</th>
                <th>Share Price at Time of Transaction</th>
                <th>Time of Transaction</th>
            </tr>
        </thead>
        <?php foreach ($rows as $row): ?>
        <tbody>
            <tr>
                <td><?= $row["type"] ?></td>
                <td><?= $row["symbol"] ?></td>
                <td><?= $row["name"] ?></td>
                <td><?= $row["shares"] ?></td>
                <td>$<?= number_format($row["price"], 2, '.', '') ?></td>
                <td><?= $row["time"] ?></td>
            </tr>
        </tbody>
        <?php endforeach ?>
    </table>
</div>