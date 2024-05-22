<?php
include('database.php');

if(!isset($_GET['id']) || empty($_GET['id'])) {
    echo json_encode(
        array(
            "status" => "error",
            "message" => "Article ID is required.",
            "data" => null
        )
    );
    return;
}
    
$id = $_GET['id'];
$id = mysqli_real_escape_string($connection, $id);
$id = htmlspecialchars($id);
$id = strip_tags($id);
$id = stripslashes($id);
$id = trim($id);

$sql = "SELECT * FROM News WHERE ID = " . $id . " ORDER BY Date DESC";

$result = mysqli_query($connection, $sql);

if (mysqli_num_rows($result) > 0) {
    while($row = mysqli_fetch_assoc($result)) {
        $sqlUser = "SELECT * FROM Users WHERE ID = " . $row['Producer'];

        $resultUser = mysqli_query($connection, $sqlUser);
        $rowUser = mysqli_fetch_assoc($resultUser);
        
        echo json_encode(
            array(
                "status" => "success",
                "message" => "Article fetched successfully.",
                "data" => array(
                    "ID" => $row['ID'],
                    "Title" => $row['Title'],
                    "Category" => $row['Category'],
                    "Date" => $row['Date'],
                    "Contents" => $row['Contents'],
                    "Producer" => array(
                        "ID" => $rowUser['ID'],
                        "Username" => $rowUser['Username']
                    )
                )
            )
        );

        return;
    }
}

echo json_encode(
    array(
        "status" => "error",
        "message" => "Article does not exist.",
        "data" => null
    )
);
?>