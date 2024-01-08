-- Look for report from July 28, 2021 in Humphrey Street
SELECT
  description
FROM
  crime_scene_reports
WHERE
  year = 2021
  AND month = 7
  AND day = 28
  AND street = 'Humphrey Street';

-- Look for 3 Interviews
SELECT
  transcript
FROM
  interviews
WHERE
  year = 2021
  AND month = 7
  AND day = 28;

-- Look for cars that left the parking lot from Humphrey Street bakery between 10:15 and 10:25
SELECT
  bakery_security_logs.year,
  bakery_security_logs.month,
  bakery_security_logs.day,
  bakery_security_logs.hour,
  bakery_security_logs.minute,
  bakery_security_logs.activity,
  bakery_security_logs.license_plate,
  people.name,
  people.id
FROM
  people
  JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE
  bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute BETWEEN 15 AND 25
  AND bakery_security_logs.activity = 'exit'
ORDER BY
  MINUTE;

-- Look for people who withdrawed money from ATM on Leggett Street
SELECT
  atm_transactions.atm_location,
  atm_transactions.transaction_type,
  bank_accounts.account_number,
  people.name
FROM
  atm_transactions
  JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
  JOIN people ON bank_accounts.person_id = people.id
WHERE
  atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';

-- Look for people who called that day and time
SELECT
  p1.name AS caller_name,
  pc.caller,
  p2.name AS receiver_name,
  pc.receiver,
  pc.duration
FROM
  phone_calls AS pc
  JOIN people AS p1 ON pc.caller = p1.phone_number
  JOIN people AS p2 ON pc.receiver = p2.phone_number
WHERE
  pc.year = 2021
  AND pc.month = 7
  AND pc.day = 28
  AND pc.duration < 60
ORDER BY
  pc.duration DESC;

-- Mix 3 quarry to 1
SELECT
  people.name
FROM
  bakery_security_logs AS bsl
  JOIN people ON bsl.license_plate = people.license_plate
  JOIN bank_accounts ON people.id = bank_accounts.person_id
  JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
  JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE
  bsl.year = 2021
  AND bsl.month = 7
  AND bsl.day = 28
  AND bsl.hour = 10
  AND bsl.minute BETWEEN 15 AND 25
  AND bsl.activity = 'exit'
  AND atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw'
  AND phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration < 60;

-- Look for the id of Fiftyville
SELECT
  *
FROM
  airports
WHERE
  city = 'Fiftyville';

-- Look for destination city of the erliest fly 29.07.2021
SELECT
  flights.id AS flight_id,
  dest_airports.city AS destination_city
FROM
  flights
  JOIN airports AS orig_airports ON flights.origin_airport_id = orig_airports.id
  JOIN airports AS dest_airports ON flights.destination_airport_id = dest_airports.id
WHERE
  origin_airport_id = 8
  AND year = 2021
  AND month = 7
  AND day = 29
ORDER BY
  HOUR,
  MINUTE
LIMIT
  1;

-- Look for the thief on the flight
SELECT
  people.name
FROM
  airports
  JOIN flights ON destination_airport_id = airports.id
  JOIN passengers ON flights.id = passengers.flight_id
  JOIN people ON passengers.passport_number = people.passport_number
WHERE
  origin_airport_id = 8
  AND flights.id = 36
  AND flights.year = 2021
  AND flights.month = 7
  AND flights.day = 29
  AND people.name IN ('Bruce', 'Diana');

-- Look for the accomplice
SELECT
  p1.name AS caller_name,
  pc.caller,
  p2.name AS receiver_name,
  pc.receiver,
  pc.duration
FROM
  phone_calls AS pc
  JOIN people AS p1 ON pc.caller = p1.phone_number
  JOIN people AS p2 ON pc.receiver = p2.phone_number
WHERE
  pc.year = 2021
  AND pc.month = 7
  AND pc.day = 28
  AND pc.duration < 60
  AND p1.phone_number = '(367) 555-5533';