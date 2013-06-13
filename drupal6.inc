location = /favicon.ico {
	log_not_found off;
	access_log off;
}

location = /robots.txt {
	allow all;
	log_not_found off;
	access_log off;
}

location ~ \..*/.*(\.php)|(\.inc)|(\.module)$ {
	return 403;
}

# Block access to "hidden" files and directories whose names begin with a
# period. This includes directories used by version control systems such
# as Subversion or Git to store control files.
location ~ (^|/)\. {
	return 403;
}

location / {
	# This is cool because no php is touched for static content
	try_files $uri @rewrite;
}

location @rewrite {
# Some modules enforce no slash (/) at the end of the URL
# Else this rewrite block wouldn't be needed (GlobalRedirect)
	rewrite ^/(.*)$ /index.php?q=$1;
}

location ~ \.php$ {
	fastcgi_split_path_info ^(.+\.php)(/.+)$;
	#NOTE: You should have "cgi.fix_pathinfo = 0;" in php.ini
	include fastcgi_params;
	fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
	fastcgi_intercept_errors on;
	#fastcgi_pass 127.0.0.1:9000;
	fastcgi_pass unix:/var/run/php5-fpm.sock;
}

# Fighting with ImageCache? This little gem is amazing.
location ~ ^/sites/.*/files/imagecache/ {
	try_files $uri @rewrite;
}

# Don't forget storage API!
location ~ ^/system/storage/serve/ {
	try_files $uri @rewrite;
}

location ~* \.(js|css|png|jpg|jpeg|gif|ico)$ {
	expires max;
	log_not_found off;
}
