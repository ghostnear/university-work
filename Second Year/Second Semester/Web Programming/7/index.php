<?php $title='Weasel News'; include("template/top.php");?>

<header class="flex w-full p-4 border-b">
    <div class="my-auto">
        <a href="index.php" class="text-4xl"> Weasel News </a>
    </div>

    <div class="ml-auto"></div>

    <div class="my-auto">
        <a class="text-2xl hover:underline" href="task.php"> Task </a>
    </div>
</header>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">
<?php
    if (isset($_SESSION['loggedin']) && $_SESSION['loggedin'] == true) {
        echo "Welcome to the member's area, " . htmlspecialchars($_SESSION['username']) . "!";
    } else {
        include("component/login.php");
    }
?>
</main>

<?php include("template/bottom.php");?>