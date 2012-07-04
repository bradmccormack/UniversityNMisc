<?php session_start();

//check expiry of card


//$checkdate = date('z');
$checkdate=$_SESSION['creditcard_expiry'];

$date = DateTime::createFromFormat('j-M-Y', $checkdate);
$today=DateTime.now();

$firstDateTimeStamp = $firstDate->format("U");
$secondDateTimeStamp = $secondDate->format("U");
$rv = round ((($firstDateTimeStamp - $secondDateTimeStamp))/86400);

$datediff=$date-today;
echo $datediff;



/*
$now = time();
echo "now = ".$now."<br/>";
$then = strtotime($checkdate);
echo "expiry =".$then."<br/>";

$difference = ($then-$now)/86400; //days
echo $difference;
*/
//You can convert seconds to whatever denomination you need. *60 for Minutes, *3600 For Hours, etc... 




//check validity of number
if(!LuhnCheck($_SESSION['creditcard_number']))
{
	$error= "<h4> Your card is invalid !!";
	return;
}	

//http://wiki.answers.com/Q/How_do_you_compute_the_difference_in_days_between_two_dates_formatted_as_yyyy-mm-dd_in_PHP
function days_between($d1, $d2){
if($d1 >= $d2){
$dd1 = $d2;
$dd2 = $d1;
}
else{
$dd1 = $d1;
$dd2 = $d2;
}
return floor(($dd2 - $dd1) / 86400);
}



/*
//http://www.developertutorials.com/tutorials/php/calculating-difference-between-dates-php-051018-1024/
function dateDiff($dformat, $endDate, $beginDate)
{
$date_parts1=explode($dformat, $beginDate);
$date_parts2=explode($dformat, $endDate);
$start_date=gregoriantojd($date_parts1[0], $date_parts1[1], $date_parts1[2]);
$end_date=gregoriantojd($date_parts2[0], $date_parts2[1], $date_parts2[2]);
return ($end_date – $start_date);
}
*/

//http://www.codediesel.com/php/luhn-algorithm-for-validating-credit-cards/
function LuhnCheck($strDigits)
{
    $sum = 0;
    $alt = false;
    for($i = strlen($strDigits) - 1; $i >= 0; $i--) 
    {
        if($alt)
        {
           $temp = $strDigits[$i];
           $temp *= 2;
           $strDigits[$i] = ($temp > 9) ? $temp = $temp - 9 : $temp;
        }
        $sum += $strDigits[$i];
        $alt = !$alt;
    }
    return $sum % 10 == 0;
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Hi Fidelity Audio - Confirmation Page </title>
<meta name="Description" content="Brads speaker shop" />
<meta name="Keywords" content="css layout" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
<link rel="stylesheet" href="template.css" type="text/css" />
</head>
<body>
<div id="wrapper">
    <div id="header">
          <?php require("header.php");?>
    </div>

    <div id="nav">
    	<?php require("navbar.php");?>
    </div>
    
    <div id="main">
		Processing your card
    	
    	
	</div>
	
      <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>