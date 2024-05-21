<?php
include('database.php');

// JSON body decoding.
$_POST = json_decode(file_get_contents('php://input'), true);

// Check if not null.
if (!isset($_POST['username']) || !isset($_POST['password'])) {
    echo json_encode(
        array(
            "logged_in" => false,
            "message" => "Authentification failed: Username or password is empty.",
            "data" => null
        )
    );
    return;
}

// Retrieve form data.
$username = $_POST['username'];
$password = $_POST['password'];

// Prevent SQL injection.
$username = mysqli_real_escape_string($connection, $username);
$password = mysqli_real_escape_string($connection, $password);

// Query the database for the user.
$sql = "SELECT * FROM Users WHERE Username = '$username' AND Password = '$password'";

$result = mysqli_query($connection, $sql);  
$row = mysqli_fetch_array($result, MYSQLI_ASSOC);  
$count = mysqli_num_rows($result);  

if ($count == 1) {
    $_SESSION["WeaselNews_loggedin"] = true;
    $_SESSION["WeaselNews_userID"] = $row['ID'];
    $_SESSION["WeaselNews_username"] = $username;
    $_SESSION["WeaselNews_elevation"] = $row['Elevation'];
    echo json_encode(
        array(
            "logged_in" => true,
            "message" => "Authentification successful!",
            "data" => array(
                "ID" => $row['ID'],
                "username" => $username,
                "elevation" => $row['Elevation']
            ),
            "session_id" => session_id()
        )
    );
} elseif($count == 0) {
    echo json_encode(
        array(
            "logged_in" => false,
            "message" => "Authentification failed: Username or password is incorrect.",
            "data" => null
        )
    );
}
elseif($mysqli->error){
    echo json_encode(
        array(
            "logged_in" => false,
            "message" => "A database error has occured! Please try again later.",
            "data" => null
        )
    );
}
?>
