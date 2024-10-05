<?php
include('database.php');

$sql = "SELECT DISTINCT Category FROM News";

$result = mysqli_query($connection, $sql);

$resultArray = array();

if (mysqli_num_rows($result) > 0) {
    while($row = mysqli_fetch_assoc($result)) {
        $resultArray[] = $row["Category"];
    }
}

echo json_encode($resultArray);
?>