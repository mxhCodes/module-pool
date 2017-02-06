<?php

/**
 * @file
 * Pool class file.
 */

/**
 * Pool class.
 *
 * If you want to get a pool, use pool_get().
 */
class Pool {
  protected $name;
  protected $items;

  /**
   * Pool constuctor function.
   *
   * @param string $name
   *   The name of the pool as string.
   */
  public function __construct($name) {
    $this->name = $name;
  }

  /**
   * Get the pool name / alias.
   */
  public function name() {
    return $this->name;
  }

  /**
   * Throws in a pool item.
   *
   * @param object $item
   *   The item as array or object.
   *
   * @return object
   *   The throwed in item as object.
   */
  public function throwin($item) {
    if (is_array($item)) {
      $item = (object) $item;
    }

    // Has the item already been throwed in?
    $throwedin = $this->pullout($item);
    if ($throwedin) {
      $item = $throwedin;
      return $item;
    }

    // This is a new item to throw in.
    $item->pool = $this->name();
    pool_item_save($item);
    $key = $this->itemkey($item);
    $this->items[$key] = $item;

    return $item;
  }

  /**
   * Pulls out a pool item.
   *
   * @param object $item
   *   The item as array or object.
   *   Omit if you want to pull out an arbitrary item.
   * @param bool $throwback
   *   Whether the item is being throwed back after pullout.
   *   Default is TRUE. When set to FALSE, the item will be deleted.
   *
   * @return object
   *   The pulled out item as object, FALSE if no item has been found.
   */
  public function pullout($item = NULL, $throwback = TRUE) {
    if (!isset($item)) {
      $item = pool_item_create();
    }
    elseif (is_array($item)) {
      $item = (object) $item;
    }

    $key = $this->itemkey($item);

    if (isset($this->items[$key])) {
      $item = $this->items[$key];
    }
    else {
      $query = db_select('pools', 'p')
        ->fields('p', array('itemid'))
        ->where('p.pool = :pool', array(':pool' => $this->name));

      if (isset($item->throwedin_id)) {
        $query->where('p.throwedin_id = :in_id', array(':in_id' => $item->throwedin_id));
      }
      if (isset($item->throwedby_id)) {
        $query->where('p.throwedby_id = :by_id', array(':by_id' => $item->throwedby_id));
      }
      if (isset($item->throwedin_type)) {
        $query->where('p.throwedin_type = :in_type', array(':in_type' => $item->throwedin_type));
      }
      if (isset($item->throwedby_type)) {
        $query->where('p.throwedby_type = :by_type', array(':by_type' => $item->throwedby_type));
      }
      if (isset($item->throwedin_vid)) {
        $query->where('p.throwedin_vid = :in_revision', array(':in_revision' => $item->throwedin_vid));
      }
      if (isset($item->throwedby_vid)) {
        $query->where('p.throwedby_vid = :by_revision', array(':by_revision' => $item->throwedby_vid));
      }

      $itemid = $query->execute()->fetchField();

      if ($itemid) {
        $item = pool_item_load($itemid);
      }
      else {
        $item = FALSE;
      }

      // Set shortcut key where the item has been searched.
      $this->items[$key] = $item;
      // Set concrete shortcut key for this item.
      $this->items[$this->itemkey($item)] = $item;
    }

    // The item shall be deleted constantly.
    if ($item && !$throwback) {
      // Constantly pull out the item from the pool.
      foreach ($this->items as $key => $value) {
        if ($item == $value) {
          unset($this->items[$key]);
        }
      }
      // Remove the item from the database.
      db_delete('pools')->where('itemid = :id', array(':id' => $item->itemid))
        ->execute();
      // Since the record has been removed, the itemid is not valid anymore.
      unset($item->itemid);
    }

    return $item;
  }

  /**
   * Helper function to generate the array key for the $items property.
   *
   * @param object $item
   *   The item as object.
   */
  protected function itemkey($item) {
    $key = array();
    $key[] = isset($item->throwedin_type) ? $item->throwedin_type : '';
    $key[] = isset($item->throwedin_id) ? $item->throwedin_id : 'NULL';
    $key[] = isset($item->throwedin_vid) ? $item->throwedin_vid : 'NULL';
    $key[] = isset($item->throwedby_type) ? $item->throwedby_type : '';
    $key[] = isset($item->throwedby_id) ? $item->throwedby_id : 'NULL';
    $key[] = isset($item->throwedby_vid) ? $item->throwedby_vid : 'NULL';
    $key = implode('_', $key);
    return $key;
  }

}
