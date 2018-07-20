#pragma once

#include <golos/plugins/private_message/private_message_objects.hpp>
#include <golos/plugins/private_message/private_message_plugin.hpp>
#include <golos/chain/database.hpp>
#include <golos/chain/evaluator.hpp>

namespace golos { namespace plugins { namespace private_message {

    class private_message_evaluator:
        public golos::chain::evaluator_impl<private_message_evaluator, private_message_plugin_operation>
    {
    public:
        using operation_type = private_message_operation;

        private_message_evaluator(database& db, private_message_plugin* plugin)
            : golos::chain::evaluator_impl<private_message_evaluator, private_message_plugin_operation>(db),
              plugin_(plugin)
        {}

        void do_apply(const private_message_operation& o);

        private_message_plugin* plugin_;
    };

} } }
