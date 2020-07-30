<?php
	$divStyle = 'position:absolute;';
	$div = "<div style = \"background-color: yellow; width: 47px; height: 50px;". $divStyle . "\"></div>";
	$div1 = "<div style = \"background-color: red; width: 67px; height: 80px;". $divStyle . "\"></div>";
	$div2 = "<div style = \"background-color: blue; width: 90px; height: 60px;". $divStyle . "\"></div>";
?>

<script src="./backup.js"></script>

<html>
	<title>
		Grid Test
	</title>

	<body style = "background-color: black;">
		<?php for($a = 0; $a < 40; ++$a):?>

			<?php $randValue = rand(1, 3); ?>

			<?php if($randValue == 1): ?>
				<?=$div?>
			<?php endif?>

			<?php if($randValue == 2): ?>
				<?=$div1?>
			<?php endif?>

			<?php if($randValue == 3): ?>
				<?=$div2?>
			<?php endif?>

		<?php endfor?>
	
		<table id = "table" style = "border: 1px solid green; border-collapse: collapse">
			<?php for($a = 0; $a < 30; ++$a): ?>
				<tr>
					<?php for($b = 0; $b < 40; ++$b): ?>
						<td id="<?=($a * 30 + $b)?>" 
							style = "border: 1px solid green; 
									width:20px; 
									height:20px;"
						>
						</td>
					<?php endfor?>
				</tr>
			<?php endfor?>
		</table>
	</body>
