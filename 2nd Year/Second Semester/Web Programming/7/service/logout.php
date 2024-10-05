<?php
include('database.php');

$_SESSION["WeaselNews_loggedin"] = false;
$_SESSION["WeaselNews_username"] = "";
$_SESSION["WeaselNews_elevation"] = 0;
$_SESSION["WeaselNews_userID"] = 0;

header("Location: ../index.php");
exit;
?>
