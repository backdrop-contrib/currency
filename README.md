Currency
========


This module provides visitors to your web site with currency conversion rates.

It also provides a callable API for currency conversion that other modules can
use.

It relies on Yahoo! Finance for getting the currency exchange data.

Features:
---------

This module provides several options that customize its look and feel:

- An overview section on the top of the page can contain any text you want

- Users can enter an amount, and that amount will calculated in the target
  currency.

- Provides an input format filter that converts currency tokens like:
  [currency:from:to:value:decimals] to a currency exchange rate.
  The 'decimals' parameter is optional.
  Example: [currency:EUR:USD:100:2].

- Provides a link to a detailed history and chart page on Yahoo Finance.

- All currency conversion operations are logged to the watchdog (optional).

- Provides a callable API for other modules to do currency exchange
  calculations. See currency.api.php for details.


Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules

- Allow access to the module under admin/access.
   You can enable it for authenticated and/or anonymous users, depending on
   your web site needs.

- Configure the module under admin/config/regional/currency

- Use the form at path '/currency'

Author
------
Khalid Baheyeldin (http://baheyeldin.com/khalid and http://2bits.com)

Maintainer
----------
Ported to Backdrop by Andy Shillingford (https://github.com/docwilmot)
