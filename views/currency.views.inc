<?php

/**
 * @file
 *   Register all of the basic handlers that views uses.
 */

/**
 * Implements hook_views_data().
 */
function currency_views_data() {
  $data['currency']['table']['group'] = t('Currency');

  $data['currency']['table']['base'] = array(
    'field' => 'currency_from',
    'title' => t('Exchange Rates'),
    'help' => t('Exchange rates provided by the currency_api module'),
  );

  $data['currency']['currency_from'] = array(
    'title' => t('Currency from'),
    'help' => t('The currency that the amount is converted from'),
    'field' => array(
      'handler' => 'currency_handler_field_currency',
    ),
    'argument' => array(
      'handler' => 'currency_handler_argument_currency',
    ),
    'filter' => array(
      'handler' => 'currency_handler_filter_currency',
    ),
  );

  $data['currency']['currency_to'] = array(
    'title' => t('Currency to'),
    'help' => t('The currency that the amount is converted to'),
    'field' => array(
      'handler' => 'currency_handler_field_currency',
    ),
    'argument' => array(
      'handler' => 'currency_handler_argument_currency',
    ),
    'filter' => array(
      'handler' => 'currency_handler_filter_currency',
    ),
  );

  $data['currency']['rate'] = array(
    'title' => t('Exchange rate'),
    'help' => t('The exchange rate used for conversion'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
  );

  $data['currency']['timestamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('The time that the exchange rate was last updated'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
  );

  return $data;
}

/**
 * Calls currency_api_convert for every exchange rate that should be displayed
 * according to filter and argument settings to ensure that rates are in the
 * database when views performs it's query.
 */
function currency_views_preload($view) {
  static $processed = FALSE;

  if (!$processed) {
    // $this->value for keyed array of selected currencies
    if ($view->filter['currency_from']) {
      $selected_from = _currency_views_get_selected_options($view->filter['currency_from']->value);
    }
    elseif ($view->argument['currency_from'] && $currency_from = $view->argument['currency_from']->get_value()) {
      // process argument
      $selected_from = array($currency_from);
    }

    if ($view->filter['currency_to']) {
      $selected_to = _currency_views_get_selected_options($view->filter['currency_to']->value);
    }
    elseif ($view->argument['currency_to'] && $currency_to = $view->argument['currency_to']->get_value()) {
      $selected_to = array($currency_to);
    }

    if ($selected_from && $selected_to) {
      // selected currencies - make sure exchange rates are in database by calling currency_api for each from/to currency combination
      foreach ($selected_from as $currency_from) {
        foreach ($selected_to as $currency_to) {
          currency_api_convert($currency_from, $currency_to);
        }
      }
    }

    $processed = TRUE;
  }
}

/**
 * Helper function to get the filter's selected options.
 */
function _currency_views_get_selected_options($options) {
  foreach ($options as $key => $set) {
    if ($set) {
      // i.e. not equal to 0
      $selected_options[] = $set;
    }
  }

  return $selected_options;
}
