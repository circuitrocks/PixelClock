#include "main.h"

/** Structure to keep the local time */
struct tm timeinfo;

Ticker getNtp;

/**
 * Initialize NTP client
 * @return <code>bool</code>
 *		true if time was updated within 10 seconds
 */
bool initNTP()
{
	getNtp.attach(3600, tryGetTime);

	configTzTime("UTC-8:00", "0.asia.pool.ntp.org", "1.asia.pool.ntp.org", "2.asia.pool.ntp.org");
	if (getLocalTime(&timeinfo, 10000))
	{ // wait up to 10sec to sync
		return true;
	}
	return false;
}

/**
 * Try to get time from NTP server
 */
void tryGetTime()
{
	getLocalTime(&timeinfo, 0);
}
