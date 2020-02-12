FROM perl:5.30
RUN cpanm --notest Dancer
COPY id.pl /id.pl
ENTRYPOINT ["/id.pl"]
