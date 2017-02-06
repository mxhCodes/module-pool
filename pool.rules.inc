<?php
/**
 * @file
 * Rules integration for the pool module.
 */

/**
 * Implements hook_rules_condition_info().
 */
function pool_rules_condition_info() {
  return array(
    'pool_throwedin' => array(
      'label' => t('An entity is inside a certain pool'),
      'parameter' => array(
        'pool' => array(
          'type' => 'text',
          'label' => t('Pool name or alias'),
        ),
        'throwedin' => array(
          'type' => 'entity',
          'label' => t('Throwed in entity'),
          'description' => t('Specifies the throwed in entity.'),
          'wrapped' => TRUE,
          'optional' => TRUE,
          'default value' => NULL,
        ),
        'throwedin_type' => array(
          'type' => 'token',
          'label' => t('Throwed in type'),
          'description' => t('Specifies the type of the throwed in entity.'),
          'options list' => 'pool_rules_entitytype_options',
          'restriction' => 'input',
          'optional' => TRUE,
          'default value' => 'entity',
        ),
        'throwedin_revisioning' => array(
          'type' => 'boolean',
          'label' => t('Respect revisioning of throwed in entity'),
          'optional' => TRUE,
          'default_value' => TRUE,
          'restriction' => 'input',
        ),
        'throwedby' => array(
          'type' => 'entity',
          'label' => t('Throwed by entity'),
          'description' => t('Specifies the throwed by entity.'),
          'wrapped' => TRUE,
          'optional' => TRUE,
          'default value' => NULL,
        ),
        'throwedby_type' => array(
          'type' => 'token',
          'label' => t('Throwed by type'),
          'description' => t('Specifies the type of the throwed by entity.'),
          'options list' => 'pool_rules_entitytype_options',
          'restriction' => 'input',
          'optional' => TRUE,
          'default value' => 'entity',
        ),
        'throwedby_revisioning' => array(
          'type' => 'boolean',
          'label' => t('Respect revisioning of throwed by entity'),
          'optional' => TRUE,
          'default_value' => FALSE,
          'restriction' => 'input',
        ),
      ),
      'group' => t('Entity Pools'),
      'base' => 'pool_rules_throwedin_condition',
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function pool_rules_action_info() {
  return array(
    'pool_throwin' => array(
      'label' => t('Throw entity into pool'),
      'parameter' => array(
        'pool' => array(
          'type' => 'text',
          'label' => t('Pool name or alias'),
        ),
        'throwedin' => array(
          'type' => 'entity',
          'label' => t('Entity to throw in'),
          'description' => t('Specifies the entity being throwed.'),
          'wrapped' => TRUE,
        ),
        'throwedin_revisioning' => array(
          'type' => 'boolean',
          'label' => t('Respect revisioning of entity being throwed.'),
          'optional' => TRUE,
          'default_value' => FALSE,
          'restriction' => 'input',
        ),
        'throwedby' => array(
          'type' => 'entity',
          'label' => t('Thrower'),
          'description' => t('Optionally specifies an entity as thrower.'),
          'wrapped' => TRUE,
        ),
        'throwedby_revisioning' => array(
          'type' => 'boolean',
          'label' => t('Respect revisioning of thrower'),
          'optional' => TRUE,
          'default_value' => FALSE,
          'restriction' => 'input',
        ),
      ),
      'group' => t('Entity Pools'),
      'base' => 'pool_rules_throwin_action',
    ),
    'pool_pullout' => array(
      'label' => t('Pull out entity from pool'),
      'parameter' => array(
        'pool' => array(
          'type' => 'text',
          'label' => t('Pool name or alias'),
        ),
        'throwedin' => array(
          'type' => 'entity',
          'label' => t('Throwed in entity'),
          'description' => t('Specifies the throwed in entity.'),
          'wrapped' => TRUE,
          'optional' => TRUE,
          'default value' => NULL,
        ),
        'throwedin_type' => array(
          'type' => 'token',
          'label' => t('Throwed in type'),
          'description' => t('Specifies the type of the throwed in entity.'),
          'options list' => 'pool_rules_entitytype_options',
          'restriction' => 'input',
          'optional' => TRUE,
          'default value' => 'entity',
        ),
        'throwedin_revisioning' => array(
          'type' => 'boolean',
          'label' => t('Respect revisioning of throwed in entity'),
          'optional' => TRUE,
          'default_value' => TRUE,
          'restriction' => 'input',
        ),
        'throwedby' => array(
          'type' => 'entity',
          'label' => t('Throwed by entity'),
          'description' => t('Specifies the throwed by entity.'),
          'wrapped' => TRUE,
          'optional' => TRUE,
          'default value' => NULL,
        ),
        'throwedby_type' => array(
          'type' => 'token',
          'label' => t('Throwed by type'),
          'description' => t('Specifies the type of the throwed by entity.'),
          'options list' => 'pool_rules_entitytype_options',
          'restriction' => 'input',
          'optional' => TRUE,
          'default value' => 'entity',
        ),
        'throwedby_revisioning' => array(
          'type' => 'boolean',
          'label' => t('Respect revisioning of throwed by entity'),
          'optional' => TRUE,
          'default_value' => FALSE,
          'restriction' => 'input',
        ),
        'throwback' => array(
          'type' => 'text',
          'label' => t('Throwback behavior'),
          'description' => t('Whether the pulled out entity shall be throwed back into the pool or not.'),
          'optional' => TRUE,
          'default value' => 'throwback',
          'options list' => 'pool_rules_throwback_options',
        ),
      ),
      'provides' => array(
        'throwedin' => array(
          'type' => 'unknown',
          'label' => t('Throwed in entity'),
        ),
        'throwedby' => array(
          'type' => 'unknown',
          'label' => t('Throwed by entity'),
        ),
      ),
      'group' => t('Entity Pools'),
      'base' => 'pool_rules_pullout_action',
    ),
  );
}

/**
 * Rules condition to check whether an entity is inside a certain pool.
 */
function pool_rules_throwedin_condition($pool, $throwedin_wrapped, $throwedin_type, $throwedin_revisioning, $throwedby_wrapped, $throwedby_type, $throwedby_revisioning) {
  $item = _pool_rules_pullout($pool, $throwedin_wrapped, $throwedin_type, $throwedin_revisioning, $throwedby_wrapped, $throwedby_type, $throwedby_revisioning);
  return (bool) $item;
}

/**
 * Rules action to let an entity throw another entity into a certain pool.
 */
function pool_rules_throwin_action($pool, $throwedin_wrapped, $throwedin_revisioning, $throwedby_wrapped, $throwedby_revisioning) {
  $throwedin = $throwedin_wrapped->value();
  $throwedin_type = $throwedin_wrapped->type();
  $throwedby = $throwedby_wrapped->value();
  $throwedby_type = $throwedby_wrapped->type();

  $item = pool_item_create($throwedin, $throwedin_type, $throwedby, $throwedby_type);
  if (!$throwedin_revisioning) {
    $item->throwedin_vid = NULL;
  }
  if (!$throwedby_revisioning) {
    $item->throwedby_vid = NULL;
  }

  pool_throwin($pool, $item);
}

/**
 * Rules action to pull out an entity from a certain pool.
 */
function pool_rules_pullout_action($pool, $throwedin_wrapped, $throwedin_type, $throwedin_revisioning, $throwedby_wrapped, $throwedby_type, $throwedby_revisioning, $throwback, $settings) {
  $return = array('throwedin' => NULL, 'throwedby' => NULL);

  $item = _pool_rules_pullout($pool, $throwedin_wrapped, $throwedin_type, $throwedin_revisioning, $throwedby_wrapped, $throwedby_type, $throwedby_revisioning);

  if ($item) {
    $throwedin = entity_load($item->throwedin_type, array($item->throwedin_id));
    $throwedby = entity_load($item->throwedby_type, array($item->throwedby_id));
    if (!empty($throwedin)) {
      $throwedin = reset($throwedin);
      $throwedin_type = $item->throwedin_type;
      $return['throwedin'] = $throwedin;
      // Provide a wrapper instead of the entity
      // when type hasn't been specified before.
      if (!isset($settings['throwedin_type'])) {
        $return['throwedin'] = entity_metadata_wrapper($throwedin_type, $throwedin);
      }
    }
    if (!empty($throwedby)) {
      $throwedby = reset($throwedby);
      $throwedby_type = $item->throwedby_type;
      $return['throwedby'] = $throwedby;
      if (!isset($settings['throwedby_type'])) {
        $return['throwedby'] = entity_metadata_wrapper($throwedby_type, $throwedby);
      }
    }

    switch ($throwback) {
      case 'no_throwback':
        pool_item_delete($item->itemid);
        break;

      case 'no_throwback_all':
        // The throwed in entity will be constantly pulled out
        // of the pool, no matter who or what else threw it in.
        while (TRUE) {
          $item = pool_item_create($throwedin, $throwedin_type);
          if (!$throwedin_revisioning) {
            $item->throwedin_vid = NULL;
          }
          if (!$throwedby_revisioning) {
            $item->throwedby_vid = NULL;
          }
          $item = pool_pullout($pool, $item);
          if ($item) {
            pool_item_delete($item->itemid);
          }
          else {
            break;
          }
        }
        break;

    }
  }

  return $return;
}

/**
 * Info alteration callback for the pool_pullout action.
 */
function pool_rules_pullout_action_info_alter(&$element_info, RulesAbstractPlugin $element) {
  if (isset($element->settings['throwedin_type'])) {
    $element_info['provides']['throwedin']['type'] = $element->settings['throwedin_type'];
  }
  if (isset($element->settings['throwedby_type'])) {
    $element_info['provides']['throwedby']['type'] = $element->settings['throwedby_type'];
  }
}

/**
 * Options list callback for the Rules throwback option.
 */
function pool_rules_throwback_options() {
  return array(
    'throwback' => t('Throwback'),
    'no_throwback' => t("Current thrower won't throw entity back"),
    'no_throwback_all' => t('Keep entity outside the pool'),
  );
}

/**
 * Options list callback for the Rules throwedin_type and throwedby_type option.
 */
function pool_rules_entitytype_options($element, $name = NULL) {
  $options = array('entity' => t('-Not specified-'));
  $options += rules_entity_action_type_options($element, $name);
  return $options;
}

/**
 * Helper function to pull out a pool item with Rules-provided parameters.
 */
function _pool_rules_pullout($pool, $throwedin_wrapped, $throwedin_type, $throwedin_revisioning, $throwedby_wrapped, $throwedby_type, $throwedby_revisioning) {
  // Get the entity objects from wrappers.
  $throwedin = isset($throwedin_wrapped) ? $throwedin_wrapped->value() : NULL;
  $throwedby = isset($throwedby_wrapped) ? $throwedby_wrapped->value() : NULL;

  // Set the proper type values when entities are defined as arguments.
  $throwedin_type = isset($throwedin_wrapped) ? $throwedin_wrapped->type() : $throwedin_type;
  $throwedby_type = isset($throwedby_wrapped) ? $throwedby_wrapped->type() : $throwedby_type;

  // Fix: When entity type is not specified, the value is set to 'entity' for Rules.
  // When entity is not specified in pool module, it should be set to NULL.
  $throwedin_type = $throwedin_type != 'entity' ? $throwedin_type : NULL;
  $throwedby_type = $throwedby_type != 'entity' ? $throwedby_type : NULL;

  $item = pool_item_create($throwedin, $throwedin_type, $throwedby, $throwedby_type);
  if (!$throwedin_revisioning) {
    $item->throwedin_vid = NULL;
  }
  if (!$throwedby_revisioning) {
    $item->throwedby_vid = NULL;
  }

  return pool_pullout($pool, $item);
}
