<?php
/**
 * @file
 * Feeds tamper plugins provided by the farm import module.
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function farm_import_feeds_tamper_default() {
  $export = array();

  // Load asset types.
  $asset_types = farm_asset_types();

  // Add asset tamper plugins.
  foreach ($asset_types as $bundle => $type) {

    // Make asset name field required.
    $feeds_tamper = farm_import_feeds_tamper_plugin('farm_asset', $bundle, 'Name', 'required');
    $export[$feeds_tamper->id] = $feeds_tamper;

    // Convert active to boolean.
    $feeds_tamper = farm_import_feeds_tamper_plugin('farm_asset', $bundle, 'Active', 'convert_boolean');
    $export[$feeds_tamper->id] = $feeds_tamper;

    // Default assets to active (if a value isn't provided).
    $feeds_tamper = farm_import_feeds_tamper_plugin('farm_asset', $bundle, 'Active', 'default_value', '1');
    $feeds_tamper->weight = 1;
    $export[$feeds_tamper->id] = $feeds_tamper;

    // If a "Parent IDs" field exists, explode it into an array of IDs.
    if (!empty(field_info_instance('farm_asset', 'field_farm_parent', $bundle))) {
      $feeds_tamper = farm_import_feeds_tamper_plugin('farm_asset', $bundle, 'Parent IDs', 'explode');
      $export[$feeds_tamper->id] = $feeds_tamper;
    }
  }

  // Load log types.
  $log_types = log_types();

  // Add log tamper plugins.
  foreach ($log_types as $bundle => $type) {

    // Convert date to timestamp.
    $feeds_tamper = farm_import_feeds_tamper_plugin('log', $bundle, 'Date', 'strtotime');
    $export[$feeds_tamper->id] = $feeds_tamper;

    // Make date field required.
    $feeds_tamper = farm_import_feeds_tamper_plugin('log', $bundle, 'Date', 'required');
    $feeds_tamper->weight = 1;
    $export[$feeds_tamper->id] = $feeds_tamper;

    // Convert done to boolean.
    $feeds_tamper = farm_import_feeds_tamper_plugin('log', $bundle, 'Done', 'convert_boolean');
    $export[$feeds_tamper->id] = $feeds_tamper;

    // Default logs to done (if a value isn't provided).
    $feeds_tamper = farm_import_feeds_tamper_plugin('log', $bundle, 'Done', 'default_value', '1');
    $feeds_tamper->weight = 1;
    $export[$feeds_tamper->id] = $feeds_tamper;

    // If an "Asset IDs" field exists, explode it into an array of IDs.
    if (!empty(field_info_instance('log', 'field_farm_asset', $bundle))) {
      $feeds_tamper = farm_import_feeds_tamper_plugin('log', $bundle, 'Asset IDs', 'explode');
      $export[$feeds_tamper->id] = $feeds_tamper;
    }

    // If an "Areas" field exists, explode it into an array of area names.
    if (!empty(field_info_instance('log', 'field_farm_area', $bundle))) {
      $feeds_tamper = farm_import_feeds_tamper_plugin('log', $bundle, 'Areas', 'explode');
      $export[$feeds_tamper->id] = $feeds_tamper;
    }

    // If a "Categories" field exists, explode it into an array of category
    // names.
    if (!empty(field_info_instance('log', 'field_farm_log_category', $bundle))) {
      $feeds_tamper = farm_import_feeds_tamper_plugin('log', $bundle, 'Categories', 'explode');
      $export[$feeds_tamper->id] = $feeds_tamper;
    }
  }

  return $export;
}
