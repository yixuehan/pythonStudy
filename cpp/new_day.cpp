#include <stdio.h>
#include <time.h>
#include <unistd.h>

auto day = 3600 * 24;
auto hour = 3600;
auto minute = 60;
auto day_test = 0;//15 * hour + 3 * minute;
auto sleep_time = 5;

int get_zone()
{
    time_t time_utc = 0;
    struct tm *p_tm_time;
    int time_zone = 0;
     
    p_tm_time = localtime( &time_utc );   //转成当地时间
    time_zone = ( p_tm_time->tm_hour > 12 ) ?   ( p_tm_time->tm_hour-=  24 )  :  p_tm_time->tm_hour;
    printf("zone:%d\n", time_zone);
    return time_zone;
    //time_t now = time(NULL);
    //time_t local = mktime(localtime(&now));
    //time_t gmt = mktime(gmtime(&now));
    //timezone = static_cast<long> (gmt - local);
    //printf("zone:%ld\n", timezone);
    //return timezone;
}

bool is_new_day()
{
    while(1) {
        time_t t = time(NULL);
        // 时区
        auto curr_time = t  + get_zone() * hour;
        auto time_left = day - (( curr_time - day_test) % day);
        if (time_left >= (day-sleep_time-1) || time_left == 0) {
            printf("new_day, curr_time:%ld, left:%ld\n", curr_time % day, time_left);
            sleep(23*hour);
            return true;
        }
        printf("curr_time:%ld, left:%ld\n", curr_time % day, time_left);
        sleep(sleep_time);
        // return false;
    }
    return false;

}

int main()
{
    while(1)
        printf("%d\n", is_new_day());
}
