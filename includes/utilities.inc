<?php

/**
 * @file
 * Utility functions for the islandora fits module.
 */

/**
 * Checks fits path for an executable.
 *
 * @param string $path
 *   Path to a desired executable, or executable string.
 *
 * @return array
 *   Errors encountered executing the file. If it returns an empty array,
 *   then the file was executable.
 */
function islandora_fits_path_check($path) {
  module_load_include('inc', 'islandora', 'includes/utilities');
  $allowed_paths = array(
    'fits.sh',
    'fits',
  );
  $errors = array();
  // Check if the given value is whitelisted.
  if (!in_array($path, $allowed_paths)) {
  // If not, check whether the given file exists.
    if (!is_file($path)) {
      $errors[] = t('The specified file path %file does not exist.', array('%file' => $path));
    }
  // If it exists, check if it's executable.
    elseif (!is_executable($path)) {
      $errors[] = t('The specified file path %file is not executable.', array('%file' => $path));
    }
  }
  // Ensure that if this is a Windows server, $file isn't pointing to a
  // shell script (that combo may cause the page to hang).
  if ((islandora_deployed_on_windows()) && (strpos($path, ".sh") == FALSE)) {
    $errors[] = t('Islandora appears to be running on Windows, but the path given ends in .sh.');
  }
  // If we haven't had errors so far, try executing it with the -v option.
  if (empty($errors)) {
    $command = $path . ' -v';
    exec($command, $output, $return_value);
    if ($return_value !== 0) {
      $errors[] = t('The command %file is not a valid FITS executable.', array('%file' => $path));
    }
  }
  if (!empty($errors)) {
    $errors[] = t("FITS derivatives will not be created.");
  }
  return $errors;
}
