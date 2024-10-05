<?php $title='Error | Weasel News'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">
    <div class="flex flex-col items-center">
        <span class="text-4xl font-bold">An error occured:</span>
        <span class="text-2xl mt-4"><?php echo $error; ?></span>
        <a class="text-2xl mt-4 hover:underline" href="<?php echo $backlink; ?>">Back</a>
    </div>
</main>

<?php include("template/bottom.php");?>