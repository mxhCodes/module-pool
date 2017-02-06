<?php

/**
 * @file
 * Definition of pool_views_handler_filter_equality.
 */

/**
 * A handler to filter by entities which (have been) throwed in.
 *
 * You can filter by the pool the entity has been throwed in,
 * or the entity which has throwed in an item.
 *
 * @ingroup views_filter_handlers
 */
class pool_views_handler_filter_equality extends views_handler_filter_equality {

  /**
   * Overrides value_form().
   */
  public function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    $form['value']['#title'] = t('Pool name or alias');
  }

}
