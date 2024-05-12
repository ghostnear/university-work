<?php
    include('service/database.php');

    $sql = "SELECT * FROM News ORDER BY Date DESC";

    $result = mysqli_query($connection, $sql);

    if (mysqli_num_rows($result) > 0) {
        while($row = mysqli_fetch_assoc($result)) {
            $sqlUser = "SELECT * FROM Users WHERE ID = " . $row['Producer'];

            $resultUser = mysqli_query($connection, $sqlUser);
            $rowUser = mysqli_fetch_assoc($resultUser);

            echo '<div class="flex flex-col border-b border-gray-400 py-4">';
            echo '<div class="flex">';
            echo '<a class="text-2xl hover:underline font-bold" href="news.php?id=' . $row['ID'] . '">' . $row['Title'] . '</a>';
            echo '<div class="text-sm my-auto ml-2"> posted in ' . $row['Category'] . '</div>';
            echo '<div class="ml-auto text-sm">' . $row['Date'] . '</div>';
            echo '</div>';
            echo '<div class="text-sm"> By ' . $rowUser['Username'] . '</div>';
            echo '</div>';
        }
    } else {
        echo '<div class="text-2xl text-center"> No news available. </div>';
    }
?>