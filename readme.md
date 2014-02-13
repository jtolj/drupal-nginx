Drupal (6/7) Nginx/PHP-FM Configuration
=======================================

Basic Drupal6/7 Site Configurations for Nginx/PHP-FPM.

Adapted from http://wiki.nginx.org/Drupal and https://github.com/perusio/drupal-with-nginx

Usage inside /etc/nginx/sites-enabled/yoursite.com:
```
server {
  server_name yoursite.com;
  root /srv/www/yoursite.com;
  index index.php;
  
  location /mycustomlocation {
    auth_basic  "Authenticate";
    auth_basic_user_file htpasswd;
  }
  
  include /etc/nginx/templates/drupal-nginx/drupal7.inc;
  include /etc/nginx/templates/drupal-nginx/microcache.inc; #if you would like to include microcaching 
}
```

To enable microcaching, you should also add/modify the following block to your nginx.conf
```
 #Microcache settings
 
        # Configure cache bypass triggers below. Be sure to add any additional variables to
        # the $no_cache map directive.

        ## Do not cache the results of POST requests
        map $request_method $no_cache_method {
               default 0;
               POST 1;
               # Uncomment to prevent cache of HEAD requests.
               # If you use an uptime monitoring service that uses HEAD requests, you will have
               # more immediate notification of outages with the below uncommented.
               #HEAD 1;
        }

        ## Testing for the session cookie being present. If there is then no
        ## caching is to be done.
        map $http_cookie $no_cache_cookie {
                default 0;
                ~SESS 1; # PHP session cookie
        }

        ## Exclude some specific items from microcache
        map $query_string $no_cache_query {
                default 0;
                ~simpleads\/load 1; #exclude simpleads requests
                ~nocache=1 1; #exclude ajax blocks and provide for manual cache override
        }

        ## Combine all  results to get the cache bypass mapping.
        map $no_cache_method$no_cache_cookie$no_cache_query $no_cache {
                default 1;
                000 0;
        }

        # Adjust the cache path, max_size, and other options as needed.
        # http://nginx.org/en/docs/http/ngx_http_fastcgi_module.html#fastcgi_cache_path
        fastcgi_cache_path /srv/nginx/cache levels=1:2 keys_zone=microcache:5M max_size=1G inactive=2h loader_threshold=2592000000 loader_sleep=1 loader_files=100000;
```
