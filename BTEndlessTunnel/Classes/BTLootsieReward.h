//
//  BTLootsieReward.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/12/15.
//
//

#ifndef BTEndlessTunnel_BTLootsieReward_h
#define BTEndlessTunnel_BTLootsieReward_h

class BTLootsieReward
{
public:
    std::string brand_name;
    std::string reward_description;
    std::string reward_id;
    // engagements

    // image_urls
    std::string imageURL_DETAIL;
    std::string imageURL_L;
    std::string imageURL_M;
    std::string imageURL_S;
    std::string imageURL_XL;
    
    int is_limited_time;
    int is_new;
    int lp;
    std::string name;
    int redemptions_remaining;
    std::string text_to_share;
    std::string tos_text;
    std::string tos_url;
    
    
};

#endif
