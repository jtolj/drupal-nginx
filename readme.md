Drupal (6/7) Nginx/PHP-FM Configuration
=======================================

Basic Drupal6/7 Site Configurations for Nginx/PHP-FPM.

Adapted from http://wiki.nginx.org/Drupal

Usage inside /etc/nginx/sites-enabled/yoursite.com:
```
server {
  server_name yoursite.com
  root /srv/www/yoursite.com;
  index index.php
  
  location /mycustomlocation {
  auth_basic  "Authenticate";
  auth_basic_user_file htpasswd;
  }
  
  include /etc/nginx/templates/drupal-nginx/drupal7.inc;
}
```
