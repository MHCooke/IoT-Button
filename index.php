<?php
  $status = $_GET['status'];
  $file = "button.txt";

  if($status == 'pushed'){
    $f = fopen($file, "w");
    fwrite($f, date("H:i:s d/m/y"));
    fclose($f);
    echo "success";
  } elseif ($status == 'check') {
    $f = fopen($file, "r");
    $date = fread($f, filesize($file));
    fclose($f);

    echo $date;
  }
?>
