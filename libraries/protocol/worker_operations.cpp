#include <golos/protocol/worker_operations.hpp>
#include <golos/protocol/exceptions.hpp>
#include <golos/protocol/validate_helper.hpp>

namespace golos { namespace protocol {

    void worker_request_operation::validate() const {
        GOLOS_CHECK_PARAM_ACCOUNT(author);
        GOLOS_CHECK_PARAM(permlink, validate_permlink(permlink));

        GOLOS_CHECK_PARAM_ACCOUNT(worker);

        GOLOS_CHECK_PARAM(required_amount_min, {
            GOLOS_CHECK_ASSET_GOLOS_OR_GBG(required_amount_min);
            GOLOS_CHECK_VALUE_GT(required_amount_min.amount, 0);
        });
        GOLOS_CHECK_PARAM(required_amount_max, {
            GOLOS_CHECK_VALUE_EQ(required_amount_min.symbol, required_amount_max.symbol);
            GOLOS_CHECK_VALUE_GE(required_amount_max.amount, required_amount_min.amount);
        });

        if (vest_reward)
            GOLOS_CHECK_PARAM(vest_reward, {
                GOLOS_CHECK_ASSET_GOLOS(required_amount_min);
            });

        GOLOS_CHECK_PARAM(duration, {
            GOLOS_CHECK_VALUE_LEGE(duration, GOLOS_WORKER_REQUEST_MIN_DURATION, GOLOS_WORKER_REQUEST_MAX_DURATION);
        });
    }

    void worker_request_delete_operation::validate() const {
        GOLOS_CHECK_PARAM_ACCOUNT(author);
        GOLOS_CHECK_PARAM(permlink, validate_permlink(permlink));
    }

    void worker_request_vote_operation::validate() const {
        GOLOS_CHECK_PARAM_ACCOUNT(voter);
        GOLOS_CHECK_PARAM_ACCOUNT(author);
        GOLOS_CHECK_PARAM(permlink, validate_permlink(permlink));

        GOLOS_CHECK_PARAM(vote_percent, {
            GOLOS_CHECK_VALUE_LEGE(vote_percent, -STEEMIT_100_PERCENT, STEEMIT_100_PERCENT);
        });
    }

} } // golos::protocol
