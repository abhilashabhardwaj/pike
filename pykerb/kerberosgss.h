/**
 * Copyright (c) 2006-2009 Apple Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

/*
 * Copyright (C) EMC Corporation.  All rights reserved.
 *
 * Modified by EMC Corporation.
 */

#include <gssapi/gssapi.h>
#include <gssapi/gssapi_generic.h>
#include <gssapi/gssapi_krb5.h>

#define krb5_get_err_text(context,code) error_message(code)

#define AUTH_GSS_ERROR      -1
#define AUTH_GSS_COMPLETE    1
#define AUTH_GSS_CONTINUE    0

#define GSS_AUTH_P_NONE         1
#define GSS_AUTH_P_INTEGRITY    2
#define GSS_AUTH_P_PRIVACY      4

#define GSS_AUTH_M_DEFAULT      0
#define GSS_AUTH_M_KERBEROS     1
#define GSS_AUTH_M_NTLM         2

typedef struct {
    gss_ctx_id_t     context;
    gss_cred_id_t    cred;
    gss_name_t       server_name;
    long int         gss_flags;
    char*            username;
    char*            response;
    int              response_length;
} gss_client_state;

typedef struct {
    gss_ctx_id_t     context;
    gss_name_t       server_name;
    gss_name_t       client_name;
    gss_cred_id_t    server_creds;
    gss_cred_id_t    client_creds;
    char*            username;
    char*            targetname;
    char*            response;
    int              response_length;
} gss_server_state;

char* server_principal_details(const char* service, const char* hostname);

int authenticate_gss_client_init(const char* service, const char* user, const char* password, const char* domain, long int mechanism, long int gss_flags, gss_client_state* state);
int authenticate_gss_client_clean(gss_client_state *state);
int authenticate_gss_client_step(gss_client_state* state, int length, const char* challenge);
int authenticate_gss_client_unwrap(gss_client_state *state, int length, const char *challenge);
int authenticate_gss_client_wrap(gss_client_state* state, int length, const char* challenge, const char* user);
int inquire_gss_client_session_key(gss_client_state* state);

int authenticate_gss_server_init(const char* service, gss_server_state* state);
int authenticate_gss_server_clean(gss_server_state *state);
int authenticate_gss_server_step(gss_server_state *state, int length, const char *challenge);
