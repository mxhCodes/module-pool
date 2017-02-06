<?php

/**
 * @file
 * Views integration for the pool module.
 */

/**
 * Implements hook_views_data_alter().
 */
function pool_views_data_alter(&$data) {
  foreach (entity_get_info() as $type => $info) {
    if (!isset($data[$type]['table']['group'])) {
      continue;
    }
    $throwedin = 'pool_throwedin_' . $type;
    $data[$throwedin]['table']['group'] = $data[$type]['table']['group'];
    $data[$throwedin]['table']['join'] = array(
      $type => array(
        'table' => 'pools',
        'left_field' => $info['entity keys']['id'],
        'field' => 'throwedin_id',
        'extra' => array(
          array(
            'field' => 'throwedin_type',
            'value' => $type,
            'numeric' => FALSE,
          ),
        ),
      ),
    );
    $data[$throwedin]['pool'] = array(
      'title' => t('Has been throwed into a pool (throwedin)'),
      'filter' => array(
        'handler' => 'pool_views_handler_filter_equality',
        'help' => t('Filter out @type objects which have been throwed into a specific pool (throwedin).', array('@type' => $info['label'])),
      ),
    );
    $throwedby = 'pool_throwedby_' . $type;
    $data[$throwedby]['table']['group'] = $data[$type]['table']['group'];
    $data[$throwedby]['table']['join'] = array(
      $type => array(
        'table' => 'pools',
        'left_field' => $info['entity keys']['id'],
        'field' => 'throwedby_id',
        'extra' => array(
          array(
            'field' => 'throwedby_type',
            'value' => $type,
            'numeric' => FALSE,
          ),
        ),
      ),
    );
    $data[$throwedby]['pool'] = array(
      'title' => t('Has throwed something into a pool (throwedby)'),
      'filter' => array(
        'handler' => 'pool_views_handler_filter_equality',
        'help' => t('Filter out @type objects which have throwed an item into a specific pool (throwedby).', array('@type' => $info['label'])),
      ),
    );
  }
}
