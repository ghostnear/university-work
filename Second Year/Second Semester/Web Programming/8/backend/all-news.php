<?php
include('database.php');

$sql = "SELECT * FROM News ORDER BY Date DESC";

$result = mysqli_query($connection, $sql);

$resultArray = array();

if (mysqli_num_rows($result) > 0) {
    while($row = mysqli_fetch_assoc($result)) {
        $sqlUser = "SELECT * FROM Users WHERE ID = " . $row['Producer'];

        $resultUser = mysqli_query($connection, $sqlUser);
        $rowUser = mysqli_fetch_assoc($resultUser);
        
        $resultArray[] = array(
            "ID" => $row['ID'],
            "Title" => $row['Title'],
            "Category" => $row['Category'],
            "Date" => $row['Date'],
            "Producer" => array(
                "ID" => $rowUser['ID'],
                "Username" => $rowUser['Username']
            )
        );
    }
}

echo json_encode($resultArray);
?>