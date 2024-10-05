<?php $title='Add Article | Weasel News'; include("template/top.php");?>

<main class="w-1/2 h-full mx-auto flex justify-center flex-col">
<?php
    include('service/database.php');

    echo '<h1 class="mx-auto text-4xl mb-3 font-bold">Add Article</h1>';

    echo '<form class="flex flex-col pb-6" action="service/add.php" method="POST">';
        echo '<input type="hidden" name="producer" value="' . $_SESSION['WeaselNews_userID'] . '">';
        echo '<label class="text-2xl mb-2" for="title">Title:</label>';
        echo '<input type="text" name="title" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3">';
        
        echo '<label class="text-2xl mb-2" for="category">Category:</label>';
        echo '<input type="text" name="category" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3">';
        
        echo '<label class="text-2xl mb-2" for="contents">Contents:</label>';
        echo '<textarea class="bg-slate-800 rounded-md border border-slate-600 hover:border-white p-3 mb-4" name="contents"></textarea>';
        
        echo '<input type="submit" class="hover:cursor-pointer bg-slate-800 mx-auto w-1/2 p-3 rounded-md active:bg-slate-600 border border-slate-600 hover:border-white" value="Submit Article">';
    echo '</form>';
?>
</main>

<?php include("template/bottom.php");?>