<?php

/**
 * @file als_link_to_modal.admin.inc
 * TODO: Enter file description here.
 */

function als_link_to_modal_settings_table() {
  $header = array('URL', 'Ajax/Modal URL', 'jQuery Selector', 'Add Classes', 'Apply to Mobile', 'Operations');
  $rows = variable_get('als_link_to_modal_settings', array());
  foreach ($rows as &$row) {
    $row[] = l(t('Edit'), 'admin/config/content/als_link_to_modal/'.str_replace('/', '-', $row[0])).' / '.l(t('Delete'), 'admin/config/content/als_link_to_modal/'.str_replace('/', '-', $row[0]).'/delete'); 
  }
  $output = theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}

/**
 * Form builder.
 */
function als_link_to_modal_settings_form($form, &$form_state, $row = array()) {
  
  $form['#row'] = $row;
  
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#description' => t('url to convert (node/add/test)'),
    '#default_value' => (!empty($row))?$row[0]:'',
    '#required' => TRUE,
  );
  $form['url_to'] = array(
    '#type' => 'textfield',
    '#title' => t('Ajax/Modal URL'),
    '#description' => t('ajax / modal url (node/add/test/ajax)'),
    '#default_value' => (!empty($row))?$row[1]:'',
    '#required' => TRUE,
  );
  $form['selector'] = array(
    '#type' => 'textfield',
    '#title' => t('jQuery Selector'),
    '#description' => t('convert links in the following jquery selector only ( like \'.convert-to-modal\' )'),
    '#default_value' => (!empty($row))?$row[2]:'',
    '#required' => FALSE,
  );
  $form['classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Add classes'),
    '#description' => t('add the following classes to the link (ctools-modal ctools-modal-theme-custom)'),
    '#default_value' => (!empty($row))?$row[3]:'',
    '#required' => FALSE,
  );
  $form['mobile'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Apply to Mobile devices.'),
    '#default_value' => (!empty($row))?$row[4]:true,
    '#required' => FALSE,
  );
  $form['submit'] = array('#type' => 'submit', '#value' => (empty($row))?t('Save'):t('Update'));

  return $form;
}

/**
 * Form submit handler.
 */
function als_link_to_modal_settings_form_submit($form, &$form_state) {
  $rmrow = $form['#row'];
  
  $v = $form_state['values'];
  $rows = variable_get('als_link_to_modal_settings', array());
  $found = false;
  foreach ($rows as $key => $row) {
    if ($row[0] == $v['url']) {
      $found = true;
      $rows[$key] = array( $v['url'], $v['url_to'], $v['selector'], $v['classes'], $v['mobile'] );
      break;
    }
  }
  if (!$found) {
    foreach ($rows as $key => $row) {
      if ($row[0] == $rmrow[0]) {
        unset($rows[$key]);
        break;
      }
    }
    $row = array( $v['url'], $v['url_to'], $v['selector'], $v['classes'], $v['mobile'] );
    $rows[] = $row;
  }
  variable_set('als_link_to_modal_settings', $rows);
  drupal_goto('admin/config/content/als_link_to_modal');
}

/**
 * Delete form builder.
 */
function als_link_to_modal_settings_delete($form, &$form_state, $row) {
  $form['#row'] = $row;

  return confirm_form($form,
    t('Are you sure you want to delete the row %row?', array('%row' => $row[0])),
    'admin/config/content/als_link_to_modal',
    t('This row are completely removed from the administrative interface. This action cannot be undone.'),
    t('Delete')
  );
}

/**
 * Form submission handler for als_link_to_modal_settings_delete().
 */
function als_link_to_modal_settings_delete_submit($form, &$form_state) {
  $rmrow = $form['#row'];
  $rows = variable_get('als_link_to_modal_settings', array());
  foreach ($rows as $key => $row) {
    if ($row[0] == $rmrow[0]) {
      unset($rows[$key]);
      break;
    }
  }
  variable_set('als_link_to_modal_settings', $rows);

  drupal_set_message(t('Row %row link setting has been removed.', array('%row' => $rmrow[0])));
  $form_state['redirect'] = 'admin/config/content/als_link_to_modal';
}
