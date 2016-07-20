#include <cfreesrp.h>
#include <freesrp.hpp>

static FreeSRP::FreeSRP *_srp = nullptr;

extern "C"
{
    freesrp_status_t freesrp_init()
    {
        freesrp_status_t status = CFREESRP_ERR;

        if(_srp == nullptr)
        {
            try
            {
                _srp = new FreeSRP::FreeSRP();
                status = CFREESRP_SUCCESS;
            }
            catch(const FreeSRP::ConnectionError &e)
            {
                status = CFREESRP_CONNECTION_ERR;
            }
        }
        else
        {
            status = CFREESRP_ALREADY_INITED;
        }

        return status;
    }

    void freesrp_deinit()
    {
        if(_srp == nullptr)
        {
            return;
        }

        delete _srp;
        _srp = nullptr;
    }

    bool freesrp_fpga_loaded()
    {
        if(_srp == nullptr)
        {
            return false;
        }
        
        bool loaded = false;

        try
        {
            loaded = _srp->fpga_loaded();
        }
        catch(const FreeSRP::ConnectionError &e)
        { }

        return loaded;
    }

    freesrp_status_t freesrp_load_fpga(char *filename)
    {
        if(_srp == nullptr)
        {
            return CFREESRP_NOT_CONNECTED;
        }

        freesrp_status_t status = CFREESRP_ERR;

        try
        {
            FreeSRP::fpga_status fpga_status = _srp->load_fpga(std::string(filename));
            switch(fpga_status)
            {
                case FreeSRP::FPGA_CONFIG_DONE: status = CFREESRP_SUCCESS; break;
                case FreeSRP::FPGA_CONFIG_SKIPPED: status = CFREESRP_FPGA_SKIPPED; break;
                default: status = CFREESRP_ERR; break;
            }
        }
        catch(const FreeSRP::ConnectionError &e)
        {
            status = CFREESRP_CONNECTION_ERR;
        }

        return status;
    }

    freesrp_status_t start_rx()
    {
        if(_srp == nullptr)
        {
            return CFREESRP_NOT_CONNECTED;
        }

        freesrp_status_t status = CFREESRP_ERR;

        try
        {
            _srp->start_rx();
            status = CFREESRP_SUCCESS;
        }
        catch(const FreeSRP::ConnectionError &e)
        {
            status = CFREESRP_CONNECTION_ERR;
        }
        
        return status;
    }

    freesrp_status_t stop_rx()
    {
        if(_srp == nullptr)
        {
            return CFREESRP_NOT_CONNECTED;
        }

        freesrp_status_t status = CFREESRP_ERR;

        try
        {
            _srp->stop_rx();
            status = CFREESRP_SUCCESS;
        }
        catch(const FreeSRP::ConnectionError &e)
        {
            status = CFREESRP_CONNECTION_ERR;
        }
        
        return status;
    }

    freesrp_status_t start_tx()
    {
        if(_srp == nullptr)
        {
            return CFREESRP_NOT_CONNECTED;
        }

        freesrp_status_t status = CFREESRP_ERR;

        try
        {
            _srp->start_tx();
            status = CFREESRP_SUCCESS;
        }
        catch(const FreeSRP::ConnectionError &e)
        {
            status = CFREESRP_CONNECTION_ERR;
        }
        
        return status;
    }

    freesrp_status_t stop_tx()
    {
        if(_srp == nullptr)
        {
            return CFREESRP_NOT_CONNECTED;
        }

        freesrp_status_t status = CFREESRP_ERR;

        try
        {
            _srp->stop_tx();
            status = CFREESRP_SUCCESS;
        }
        catch(const FreeSRP::ConnectionError &e)
        {
            status = CFREESRP_CONNECTION_ERR;
        }
        
        return status;
    }

    bool freesrp_get_rx_sample(freesrp_sample_t *s)
    {
        static FreeSRP::sample samp;
        
        if(_srp == nullptr)
        {
            return false;
        }

        bool success = _srp->get_rx_sample(samp);

        if(success)
        {
            s->i = samp.i;
            s->q = samp.q;
        }

        return success;
    }

    bool freesrp_submit_tx_sample(freesrp_sample_t *s)
    {
        static FreeSRP::sample samp;

        if(_srp == nullptr)
        {
            return false;
        }

        samp.i = s->i;
        samp.q = s->q;

        return _srp->submit_tx_sample(samp);
    }

    freesrp_status_t freesrp_send_cmd(freesrp_cmd_id_t id, double param, freesrp_cmd_err_t *error, double *new_value)
    {
        if(_srp == nullptr)
        {
            return CFREESRP_NOT_CONNECTED;
        }

        freesrp_status_t status = CFREESRP_ERR;

        try
        {
            FreeSRP::command command = _srp->make_command((FreeSRP::command_id) id, param);
            FreeSRP::response response = _srp->send_cmd(command);

            *error = (freesrp_cmd_err_t) response.error;
            *new_value = response.param;

            status = CFREESRP_SUCCESS;
        }
        catch(const FreeSRP::ConnectionError &e)
        {
            status = CFREESRP_CONNECTION_ERR;
        }
        catch(const std::runtime_error &e)
        {
            status = CFREESRP_INVALID_CMD;
        }
        
        return status;
    }

    freesrp_status_t freesrp_version(freesrp_version_t *version)
    {
        if(_srp == nullptr)
        {
            return CFREESRP_NOT_CONNECTED;
        }

        FreeSRP::freesrp_version freesrp_version = _srp->version();

        version->fx3 = strdup(freesrp_version.fx3.c_str());
        version->fpga = strdup(freesrp_version.fpga.c_str());
    }
}
