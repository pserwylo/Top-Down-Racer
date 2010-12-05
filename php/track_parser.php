#!/usr/bin/php5
<?php

if ( !isset( $argv[ 1 ] ) )
{
    echo "Please specify an svg file.";
    exit;
}

$filename = $argv[ 1 ];

if ( !file_exists( $filename ) )
{
    echo "Could not find file '". $filename . "'.";
    exit;
}

$trackName = basename( $filename );
$trackName = substr( $trackName, 0, -strrpos( $trackName, "." ) );
$svg = simplexml_load_file( $filename );

$obstacles = array();

foreach( $svg->g->path as $path )
{
    // Extract the actual path information...
    $path = (string)$path['d'];

    // Make sure that we remove the leading M and the trailing z...
    $path = trim( substr( $path, 1, -1 ) );

    $obstacle = array();

    $coords = explode( " ", $path );
    foreach( $coords as $coord )
    {
        $parts = explode( ",", $coord );
        $obstacle[] = $parts;
    }
    $obstacles[] = $obstacle;
}

// Below is the template for the cpp file...
?>

#ifndef TRACK_<?php echo $trackName; ?>

#define TRACK_<?php echo $trackName; ?>


print_r( $obstacles );

#endif
