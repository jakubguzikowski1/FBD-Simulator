#ifndef DATATYPES_H
#define DATATYPES_H

/**
 * @brief Represents a simulation timestamp.
 */
struct STimeStamp {
    /**
     * @brief Whole seconds part of time.
     */
    unsigned Seconds{0U};

    /**
     * @brief Milliseconds part of time in range [0, 999].
     */
    unsigned Milliseconds{0U};

    /**
     * @brief Adds a sampling interval to the timestamp.
     * @param _msec Sampling period in milliseconds.
     */
    void addSampling(unsigned _msec) {
        Milliseconds += _msec;
        Seconds += Milliseconds / 1000U;
        Milliseconds %= 1000U;
    }

    /**
     * @brief Returns timestamp represented in seconds.
     * @return Timestamp as floating-point seconds.
     */
    double getInSeconds() const {
        return static_cast<double>(Seconds) + static_cast<double>(Milliseconds) / 1000.0;
    }
};

/**
 * @brief Data quality state for a sample.
 */
enum class DataSampleStatus {
    /**
     * @brief Valid sample value.
     */
    ok = 0,
    /**
     * @brief Invalid or unavailable sample value.
     */
    bad = 1
};

/**
 * @brief Represents one sampled numeric value with status and timestamp.
 */
struct SDataSample {
    /**
     * @brief Numeric sample value.
     */
    double Value{0.0};

    /**
     * @brief Data quality status.
     */
    DataSampleStatus Status{DataSampleStatus::bad};

    /**
     * @brief Time at which the sample is defined.
     */
    STimeStamp TimeStamp{};

    /**
     * @brief Checks whether sample is valid.
     * @return True if status equals DataSampleStatus::ok.
     */
    bool isOK() const {
        return Status == DataSampleStatus::ok;
    }
};

#endif  // DATATYPES_H
