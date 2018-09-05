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
  $errors = islandora_executable_available_check($path, $allowed_paths);

  // If no errors, try executing it with the -v option.
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
